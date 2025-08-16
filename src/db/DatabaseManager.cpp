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

std::shared_ptr<AbstractCharacter> DatabaseManager::fetchCharacter(int theCharacterID) const {
    // TODO: create character function
}

std::shared_ptr<Weapon> DatabaseManager::fetchWeapon(int theWeaponID) const {
    // TODO: create weapon creation function
}

void DatabaseManager::insertRoom(Room &room) const {

    const char *sql = R"(INSERT OR REPLACE INTO rooms
                        (id, north, south, east, west, serialMap)
                        VALUES(?, ?, ?, ?, ?, ?);
                        )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1
        , &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    room.serializeRoomMap();

    sqlite3_bind_int(stmt, 1, room.getRoomID());
    sqlite3_bind_int(stmt, 2, room.getNorth());
    sqlite3_bind_int(stmt, 3, room.getSouth());
    sqlite3_bind_int(stmt, 4, room.getEast());
    sqlite3_bind_int(stmt, 5, room.getWest());
    sqlite3_bind_text(stmt, 6, room.getSerialRoomMap().c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

//TODO:

void DatabaseManager::insertCharacter(AbstractCharacter &character) {
}

void DatabaseManager::insertCharacterType(AbstractCharacter &character) {
}

std::shared_ptr<AbstractCharacter> DatabaseManager::loadCharacter(int roomId) {
}

std::shared_ptr<AbstractCharacter> DatabaseManager::loadCharacterType(int charType) {
}

void DatabaseManager::createActiveCharacterTableIfNotExists() {
}

void DatabaseManager::createTypeTableIfNotExists() {
}

void DatabaseManager::saveRoomTable() {
}

void DatabaseManager::saveActiveCharacter() {
}

void DatabaseManager::saveTypeTable() {
}

/**
 * This loads a room from the database.
 * @param id this is the id of the room to be loaded.
 * @return This is a smart pointer to the room.
 */
std::shared_ptr<Room> DatabaseManager::loadRoom(const int id) {
    const char *sql = R"(SELECT north, south, east
                        , west, serialMap FROM rooms WHERE id = ?;)";
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
        const char *mapStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        room = std::make_shared<Room>();
        room->setRoomID(id);
        room->setNorth(north);
        room->setSouth(south);
        room->setEast(east);
        room->setWest(west);
        room->setSerialRoomMap(mapStr ? mapStr : "");
        room->setAlreadyGenerated(true);
        room->initializeRoom();
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
                                        serialMap TEXT);
                                        )";

    char *errmsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errmsg) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
        sqlite3_free(errmsg);
    }
}
