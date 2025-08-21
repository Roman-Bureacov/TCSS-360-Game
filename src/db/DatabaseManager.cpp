//
// Created by riley on 8/2/25.
//

#include "../include/DatabaseManager.h"




DatabaseManager::DatabaseManager(const std::string &theDbFile) {
    openDatabase(theDbFile);

    createRoomTableIfNotExists();

    createActiveNPCTableIfNotExists();
}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

void DatabaseManager::insertRoom(Room &theRoom) const {

    const char *sql = R"(INSERT OR REPLACE INTO rooms
                        (id, north, south, east, west, serialMap, char1, char2, char3)
                        VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?);
                        )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1
        , &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    //First run through this will do nothing
    theRoom.serializeRoomMap();

    sqlite3_bind_int(stmt, 1, theRoom.getRoomID());
    sqlite3_bind_int(stmt, 2, theRoom.getNorth());
    sqlite3_bind_int(stmt, 3, theRoom.getSouth());
    sqlite3_bind_int(stmt, 4, theRoom.getEast());
    sqlite3_bind_int(stmt, 5, theRoom.getWest());
    sqlite3_bind_text(stmt, 6, theRoom.getSerialRoomMap().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 7, theRoom.getCharacters().at(0) );
    sqlite3_bind_int64(stmt, 8, theRoom.getCharacters().at(1) );
    sqlite3_bind_int64(stmt, 9, theRoom.getCharacters().at(2 ) );

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

std::shared_ptr<Room> DatabaseManager::loadRoom(const int theId) {
    const char *sql = R"(SELECT north, south, east
                        , west, serialMap, char1
                        , char2, char3 FROM rooms WHERE id = ?;)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1
        , &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, theId);

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
        room->setRoomID(theId);
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
            + std::to_string(theId) + " not found.");

    }

    return room;
}

void DatabaseManager::openDatabase(const std::string &theDbFile) {

    int rc = sqlite3_open(theDbFile.c_str(), &db);

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
            serialMap TEXT,
            char1 INTEGER,
            char2 INTEGER,
            char3 INTEGER
            );
        )";


    char *errmsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errmsg) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
        sqlite3_free(errmsg);
        throw std::runtime_error(sqlite3_errmsg(db));
    }
}

void DatabaseManager::insertCharacter(AbstractCharacter &theCharacter) const {
    // Only handle NPCs
    auto npc = dynamic_cast<NPC*>(&theCharacter);
    if (!npc) return;

    const char *sql = R"(
        INSERT OR REPLACE INTO active_npcs
        (id, type_id, room_id, health, x, y, is_active)
        VALUES(?, ?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, npc->getID());
    sqlite3_bind_int(stmt, 2, static_cast<int>(npc->getType()));
    sqlite3_bind_int(stmt, 3, npc->getRoomId());
    sqlite3_bind_int(stmt, 4, npc->getHealth());
    sqlite3_bind_int(stmt, 5, npc->getX());
    sqlite3_bind_int(stmt, 6, npc->getY());
    sqlite3_bind_int(stmt, 7, npc->getIsActive() ? 1 : 0);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}

std::vector<std::shared_ptr<NPC>> DatabaseManager::loadCharacters(const int theRoomId) {
    const char *sql = R"(
        SELECT type_id, health, x, y, is_active
        FROM active_npcs
        WHERE room_id = ?;
    )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, theRoomId);

    std::vector<std::shared_ptr<NPC>> npcs;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int typeId = sqlite3_column_int(stmt, 0);
        int health = sqlite3_column_int(stmt, 1);
        int x = sqlite3_column_int(stmt, 2);
        int y = sqlite3_column_int(stmt, 3);
        bool isActive = sqlite3_column_int(stmt, 4) != 0;

        auto npc = loadCharacterType(typeId);
        npc->setHealth(health);
        npc->setX(x);
        npc->setY(y);
        npc->setIsActive(true);

        npcs.push_back(npc);
    }

    sqlite3_finalize(stmt);
    return npcs;
}

std::shared_ptr<NPC> DatabaseManager::loadCharacterType(int theCharType) {
    switch (static_cast<NPCType>(theCharType)) {
        case NPCType::Goblin:
            return std::make_shared<Goblin>(
                NPCStats::MYGOBLINNAME,
                NPCStats::MYGOBLINMAXHEALTH,
                NPCStats::MYGOBLINMOVEMENTSPEED
            );
        case NPCType::Skeleton:
            return std::make_shared<Skeleton>(
                NPCStats::MYSKELETONNAME,
                NPCStats::MYSKELETONMAXHEALTH,
                NPCStats::MYSKELETONMOVEMENTSPEED
            );
        case NPCType::TimCapaul:
            return NPC::timCapaulFactory();
        default:
            throw std::runtime_error("Unknown NPC type");
    }
}

void DatabaseManager::createActiveNPCTableIfNotExists() {
    const char *sql = R"(
        CREATE TABLE IF NOT EXISTS active_npcs(
            id INTEGER PRIMARY KEY,
            type_id INTEGER NOT NULL,
            room_id INTEGER NOT NULL,
            health INTEGER NOT NULL,
            x INTEGER NOT NULL,
            y INTEGER NOT NULL,
            is_active INTEGER NOT NULL
        );
    )";

    char *errmsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errmsg) != SQLITE_OK) {
        std::string errMsgCopy = errmsg ? errmsg : sqlite3_errmsg(db);
        sqlite3_free(errmsg);
        throw std::runtime_error(errMsgCopy);
    }
}
