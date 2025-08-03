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
    void insertRoom(Room &room);
    std::shared_ptr<Room> loadRoom(int id);

private:
    sqlite3 *db;

    void openDatabase(const std::string& dbFile );
    void closeDatabase();


    //Dungeon and rooms section.
    void createRoomTableIfNotExists();


};



#endif //DATABASEMANAGER_H
