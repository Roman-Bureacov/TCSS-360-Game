//
// Created by riley on 8/2/25.
//

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>
#include <string>
#include <sqlite3.h>
#include "Room.h"

/**
 * Class that handles database calls.
 * @author Riley Hopper
 * @author Roman Bureacov
 * @version 2025 August
 */
class DatabaseManager {
public:
    explicit DatabaseManager(const std::string& dbFile);
    ~DatabaseManager();



    //Dungeon and rooms section.
    void insertRoom(Room &room);
    std::shared_ptr<Room> loadRoom(int id);

    // fetchers from the database
    /**
     * Fetches a character from the database.
     * @param theCharacterID the ID of the character
     * @return the character associated with the ID
     */
    std::shared_ptr<AbstractCharacter> fetchCharacter(int theCharacterID) const;

    /**
     * Fetches a weapon from the database.
     * @param theWeaponID the ID of the weapon
     * @return the weapon object associate with the ID
     */
    std::shared_ptr<Weapon> fetchWeapon(int theWeaponID) const;

private:
    sqlite3 *db;

    void openDatabase(const std::string& dbFile );
    void closeDatabase();


    //Dungeon and rooms section.
    void createRoomTableIfNotExists();


};



#endif //DATABASEMANAGER_H
