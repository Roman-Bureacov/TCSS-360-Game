//
// Created by riley on 8/2/25.
//

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>
#include <string>
#include <sqlite3.h>
#include "Room.h"


class DatabaseManager {
public:
    explicit DatabaseManager(const std::string& dbFile);
    ~DatabaseManager();



    //Dungeon and rooms section.
    void insertRoom(int id, bool north, bool south
        , bool east, bool west, int enemyCount);
    std::shared_ptr<Room> loadRoom(int id);

private:
    sqlite3 *db;

    void openDatabase(const std::string& dbFile );
    void closeDatabase();


    //Dungeon and rooms section.
    void createRoomTableIfNotExists();


};



#endif //DATABASEMANAGER_H
