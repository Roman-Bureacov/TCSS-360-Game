//
// Created by riley on 8/2/25.
//

#include "../include/DatabaseManager.h"

#include <filesystem>


const DatabaseManager DatabaseManager::INSTANCE = DatabaseManager();
sqlite3* DatabaseManager::DATABASE = nullptr;

DatabaseManager::DatabaseManager() {
    if (std::filesystem::exists(DATABASE_PATH)) {
        sqlite3_open_v2(DATABASE_PATH, &DATABASE, SQLITE_OPEN_READWRITE, nullptr);
    } else {
        sqlite3_open_v2(DATABASE_PATH, &DATABASE, SQLITE_OPEN_CREATE, nullptr);
        setupDatabase();
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(DATABASE);
}

std::shared_ptr<AbstractCharacter> DatabaseManager::fetchCharacter(int theCharacterID) {
    // TODO: create character function
    return 0;
}

std::shared_ptr<Weapon> DatabaseManager::fetchWeapon(int theWeaponID) {
    // TODO: create weapon creation function
    return 0;
}

void DatabaseManager::insertRoom(Room &room) {

    const char *sql = R"(INSERT OR REPLACE INTO rooms
                        (id, north, south, east, west, serialMap, char1, char2, char3)
                        VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?);
                        )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(DATABASE, sql, -1
        , &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(DATABASE));
    }
    //First run through this will do nothing
    room.serializeRoomMap();

    sqlite3_bind_int(stmt, 1, room.getRoomID());
    sqlite3_bind_int(stmt, 2, room.getNorth());
    sqlite3_bind_int(stmt, 3, room.getSouth());
    sqlite3_bind_int(stmt, 4, room.getEast());
    sqlite3_bind_int(stmt, 5, room.getWest());
    sqlite3_bind_text(stmt, 6, room.getSerialRoomMap().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 7, room.getCharacters().at(0) );
    sqlite3_bind_int64(stmt, 8, room.getCharacters().at(1) );
    sqlite3_bind_int64(stmt, 9, room.getCharacters().at(2 ) );

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(DATABASE));
    }

    sqlite3_finalize(stmt);
}


void DatabaseManager::insertCharacter(AbstractCharacter &character) {
    //TODO

}

void DatabaseManager::insertCharacterType(AbstractCharacter &character) {
    //TODO

}

std::shared_ptr<AbstractCharacter> DatabaseManager::loadCharacter(int roomId) {
    //TODO

    return 0;
}

std::shared_ptr<AbstractCharacter> DatabaseManager::loadCharacterType(int charType) {
    //TODO

    return 0;
}

void DatabaseManager::createActiveCharacterTableIfNotExists() {
    //TODO

}

void DatabaseManager::createTypeTableIfNotExists() {
    //TODO

}

void DatabaseManager::saveRoomTable() {
    //TODO

}

void DatabaseManager::saveActiveCharacter() {
    //TODO

}

void DatabaseManager::saveTypeTable() {
    //TODO

}


std::shared_ptr<Room> DatabaseManager::loadRoom(const int id) {
    const char *sql = R"(SELECT north, south, east
                        , west, serialMap, char1
                        , char2, char3 FROM rooms WHERE id = ?;)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(DATABASE, sql, -1
        , &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(DATABASE));
    }

    sqlite3_bind_int(stmt, 1, id);

    std::shared_ptr<Room> room = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        bool north = sqlite3_column_int(stmt, 0);
        bool south = sqlite3_column_int(stmt, 1);
        bool east = sqlite3_column_int(stmt, 2);
        bool west = sqlite3_column_int(stmt, 3);
        const char *mapStr = reinterpret_cast<const char*>
            (sqlite3_column_text(stmt, 4));
        long long char1 = sqlite3_column_int64(stmt, 5);
        long long char2 = sqlite3_column_int64(stmt, 6);
        long long char3 = sqlite3_column_int64(stmt, 7);


        room = std::make_shared<Room>();
        room->setAlreadyGenerated(true);
        room->setRoomID(id);
        room->setNorth(north);
        room->setSouth(south);
        room->setEast(east);
        room->setWest(west);
        room->setSerialRoomMap(mapStr ? mapStr : "");
        room->setChar1ID(char1);
        room->setChar2ID(char2);
        room->setChar3ID(char3);
        room->initializeRoom();
    }

    sqlite3_finalize(stmt);

    if (!room) {
        throw std::runtime_error("Room with ID "
            + std::to_string(id) + " not found.");

    }

    return room;
}

void DatabaseManager::setupDatabase() {

    const char *sql = R"(
        CREATE TABLE IF NOT EXISTS rooms(
            id INTEGER PRIMARY KEY,
            north INTEGER,
            south INTEGER,
            east INTEGER,
            west INTEGER,
            serialMap TEXT,
            char1 INTEGER,
            char2 INTEGER,
            char3 INTEGER
            );
        )";

    char* message = nullptr;
    if (sqlite3_exec(DATABASE, sql, nullptr, nullptr, &message) != SQLITE_OK) {
        const std::string err = message ? message : "Unknown error";
        sqlite3_free(message);
        throw std::runtime_error(err);
    }

}
