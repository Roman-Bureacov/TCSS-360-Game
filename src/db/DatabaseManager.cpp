//
// Created by riley on 8/2/25.
//

#include "../include/DatabaseManager.h"

#include <filesystem>


const DatabaseManager DatabaseManager::INSTANCE = DatabaseManager();
sqlite3* DatabaseManager::INSTANCE_DATABASE = nullptr;
sqlite3* DatabaseManager::BUILD_DATABASE = nullptr;

DatabaseManager::DatabaseManager() {
    if (std::filesystem::exists(BUILD_PATH) && std::filesystem::exists(INSTANCE_PATH)) {
        sqlite3_open_v2(BUILD_PATH, &INSTANCE_DATABASE, SQLITE_OPEN_READWRITE, nullptr);
    } else {
        sqlite3_open_v2(BUILD_PATH, &INSTANCE_DATABASE,
            SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, nullptr);
        sqlite3_open_v2(INSTANCE_PATH, &BUILD_DATABASE,
            SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, nullptr);
        buildDatabase();
        insertDatabase();
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(INSTANCE_DATABASE);
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
    if (sqlite3_prepare_v2(INSTANCE_DATABASE, sql, -1
        , &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(INSTANCE_DATABASE));
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
        throw std::runtime_error(sqlite3_errmsg(INSTANCE_DATABASE));
    }

    sqlite3_finalize(stmt);
}


void DatabaseManager::insertCharacter(AbstractCharacter &character) {
    //TODO

}

void DatabaseManager::insertCharacterType(AbstractCharacter &character) {
    //TODO

}

std::shared_ptr<AbstractCharacter> DatabaseManager::loadCharacter(int characterID) {

    sqlite3_stmt* s = query(BUILD_DATABASE, R"(
        SELECT char_type, name, base_movement_speed, weapon_id
        FROM characters
        WHERE id = ?
    )");
    sqlite3_bind_int(s, 1, characterID);

    AbstractCharacter* character;
    auto name = sqlite3_column_str(s, 1);
    auto movement = sqlite3_column_int(s, 3);

    if (sqlite3_column_str(s, 0) == "NPC") {
        character = new NPC(
            name,
            100,
            movement
            );
    } // TODO: else construct player?


    sqlite3_finalize(s);

    return std::shared_ptr<AbstractCharacter>(character);
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

    sqlite3_stmt *stmt = query(INSTANCE_DATABASE, sql);

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

void DatabaseManager::buildDatabase() {

    const char* buildSql = R"(
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
        CREATE TABLE IF NOT EXISTS weapons(
            id INTEGER PRIMARY KEY,
            name TEXT,
            attack_ticks INTEGER,
            north_width INTEGER,
            north_height INTEGER,
            east_width INTEGER,
            east_height INTEGER,
            south_width INTEGER,
            south_height INTEGER,
            west_width INTEGER,
            west_height INTEGER
        );
        CREATE TABLE IF NOT EXISTS characters(
            id INTEGER PRIMARY KEY,
            char_type TEXT,
            name TEXT,
            base_movement_speed INTEGER,
            weapon_id INTEGER
        );
        )";

    const char* instanceSql = R"(
        CREATE TABLE IF NOT EXISTS active_instance(
            room_id INTEGER,
            character_id INTEGER
        )
    )";

    execute(BUILD_DATABASE, buildSql);
    execute(INSTANCE_DATABASE, instanceSql);

}

void DatabaseManager::insertDatabase() {

}

void DatabaseManager::execute(sqlite3 *database, const char *sql) {
    char* message = nullptr;
    if (sqlite3_exec(database, sql, nullptr, nullptr, &message) != SQLITE_OK) {
        const std::string err = message ? message : "Unknown error";
        sqlite3_free(message);
        throw std::runtime_error(err);
    }
}

sqlite3_stmt *DatabaseManager::query(sqlite3* database, const char *sql) {
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(database, sql, -1, &statement, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database));
    }

    return statement;
}

const char *DatabaseManager::sqlite3_column_str(sqlite3_stmt *s, int col) {
    return reinterpret_cast<const char*>(sqlite3_column_text(s, col));
}

