//
// Created by riley on 8/2/25.
//

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>
#include <string>
#include <sqlite3.h>

#include "Room.h"
#include "Bitz.h"


/**
 * Static class that handles SQLite database calls.
 * @author Riley Hopper
 * @author Roman Bureacov
 * @version 2025 August
 */
class DatabaseManager final {
public:

    /**
     * Inserts a room into the database.
     * @param room Reference to the room to be inserted.
     */
    static void insertRoom(Room &room);

    /**
     * Inserts a character into the table.
     * @param character A reference to the character to be inserted.
     */
    static void insertCharacter(AbstractCharacter &character);

    /**
     * Inserts a character type into the tabel.
     * @param character Reference to the character type to be inserted.
     */
    static void insertCharacterType(AbstractCharacter &character);

    /**
    * This loads a room from the database.
    * @param id this is the id of the room to be loaded.
    * @return This is a smart pointer to the room.
    */
    static std::shared_ptr<Room> loadRoom(int id);

    /**
     *
     * @param roomId ID of the room the character is in.
     * @return A shared pointer to the character.
     */
    static std::shared_ptr<AbstractCharacter> loadCharacter(int roomId);

    /**
     *
     * @param charType Integer representing character type.
     * @return  A shared pointer to the character.
     */
    static std::shared_ptr<AbstractCharacter> loadCharacterType(int charType);


    /**
     * Fetches a character from the database.
     * @param theCharacterID the ID of the character
     * @return the character associated with the ID
     */
    static std::shared_ptr<AbstractCharacter> fetchCharacter(int theCharacterID);

    /**
     * Fetches a weapon from the database.
     * @param theWeaponID the ID of the weapon
     * @return the weapon object associate with the ID
     */
    static std::shared_ptr<Weapon> fetchWeapon(int theWeaponID);


private:
    static constexpr const char* DATABASE_PATH = "DungeonDatabase.db";
    static sqlite3* DATABASE;
    static const DatabaseManager INSTANCE;

    /**
     * This constructs and opens the database.
     */
    explicit DatabaseManager();
    ~DatabaseManager();

    /**
     * Creates a room table if it doesn't already exist.
     */
    static void setupDatabase();

    /**
     * Creates a table for the active characters.
     */
    static void createActiveCharacterTableIfNotExists();

    /**
     * Creates a table for character types.
     */
    static void createTypeTableIfNotExists();

    /**
     * Saves the room table.
     */
    static void saveRoomTable();

    /**
     * Saves the active characters.
     */
    static void saveActiveCharacter();

    /**
     * Saves the type table.
     */
    static void saveTypeTable();
};

#endif //DATABASEMANAGER_H