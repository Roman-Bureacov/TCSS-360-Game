//
// Created by riley on 8/2/25.
//

#include "../include/DatabaseManager.h"

#include <iostream>
#include <stdexcept>
#include <bits/ostream.tcc>


DatabaseManager::DatabaseManager(const std::string &dbFile) {
    openDatabase(dbFile);

    createRoomTableIfNotExists();
}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

void DatabaseManager::insertRoom(int id, bool north, bool south
    , bool east, bool west, int enemyCount) {

    const char *sql = R"(INSERT OR REPLACE INTO rooms
                        (id, north, south, east, west, enemyCount)
                        VALUES(?, ?, ?, ?, ?, ?);
                        )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1
        , &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_int(stmt, 2, north);
    sqlite3_bind_int(stmt, 3, south);
    sqlite3_bind_int(stmt, 4, east);
    sqlite3_bind_int(stmt, 5, west);
    sqlite3_bind_int(stmt, 6, enemyCount);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

std::shared_ptr<Room> DatabaseManager::loadRoom(int id) {
    const char *sql = R"(SELECT north, south, east
                        , west, enemyCount FROM rooms WHERE id = ?;)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1
        , &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, id);

    std::shared_ptr<Room> room = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        bool north = sqlite3_column_int(stmt, 0);
        bool south = sqlite3_column_int(stmt, 1);
        bool east = sqlite3_column_int(stmt, 2);
        bool west = sqlite3_column_int(stmt, 3);
        int enemyCount = sqlite3_column_int(stmt, 4);

        room = std::make_shared<Room>();
        room->roomID = id;
        room->roomNorth = north;
        room->roomSouth = south;
        room->roomEast = east;
        room->roomWest = west;
        room->enemyAmount = enemyCount;
        room->generateRoom();
    }

    sqlite3_finalize(stmt);

    if (!room) {
        throw std::runtime_error("Room with ID "
            + std::to_string(id) + " not found.");

    }

    return room;
}

void DatabaseManager::openDatabase(const std::string &dbFile) {

    int rc = sqlite3_open(dbFile.c_str(), &db);

    if (rc != SQLITE_OK) {

        throw std::runtime_error(sqlite3_errmsg(db));


    } else {
        std::cout << "Database opened" << std::endl;

    }
}

void DatabaseManager::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

void DatabaseManager::createRoomTableIfNotExists() {

    const char *sql = R"(
        CREATE TABLE IF NOT EXISTS rooms(
        id INTEGER PRIMARY KEY,
        north INTEGER,
        south INTEGER,
        east INTEGER,
        west INTEGER,
        enemyCount INTEGER);
        )";

    char *errmsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errmsg) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
        sqlite3_free(errmsg);
    }
}
