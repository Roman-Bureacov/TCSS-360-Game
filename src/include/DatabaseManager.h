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

    //Insert, new member to table.
    void insertRoom(std::shared_ptr<Room> &room);
    void insertCharacter(AbstractCharacter &character);
    void insertCharacterType(AbstractCharacter &character);

    //Loads members from the database.
    std::shared_ptr<Room> loadRoom(int id);
    std::shared_ptr<AbstractCharacter> loadCharacter(int roomId);
    std::shared_ptr<AbstractCharacter> loadCharacterType(int charType);


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

    //This opens and closes a database
    void openDatabase(const std::string& dbFile);
    void closeDatabase();

    //Create tables, if they don't exist
    void createRoomTableIfNotExists();
    void createActiveCharacterTableIfNotExists();
    void createTypeTableIfNotExists();

    //These are the saved states of the dungeon.
    void saveRoomTable();
    void saveActiveCharacter();
    void saveTypeTable();
};

#endif //DATABASEMANAGER_H