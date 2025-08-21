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
 * Class that handles database calls.
 * @author Riley Hopper
 * @author Roman Bureacov
 * @version 2025 August
 */
class DatabaseManager {
public:

    /**
     * This constructs and opens the database.
     * @param theDbFile This is the database file.
     */
    explicit DatabaseManager(const std::string& theDbFile);
    ~DatabaseManager();

    /**
     * Inserts a room into the database.
     * @param theRoom Reference to the room to be inserted.
     */
    void insertRoom(Room &theRoom) const;

    /**
     * Inserts a character into the table.
     * @param theCharacter A reference to the character to be inserted.
     */
    void insertCharacter(AbstractCharacter &theCharacter);

    /**
     * Inserts a character type into the tabel.
     * @param theCharacter Reference to the character type to be inserted.
     */
    void insertCharacterType(AbstractCharacter &theCharacter);

    /**
    * This loads a room from the database.
    * @param theId this is the id of the room to be loaded.
    * @return This is a smart pointer to the room.
    */
    std::shared_ptr<Room> loadRoom(int theId);

    /**
     *
     * @param theRoomId ID of the room the character is in.
     * @return A shared pointer to the character.
     */
    std::shared_ptr<AbstractCharacter> loadCharacter(int theRoomId);

    /**
     *
     * @param theCharType Integer representing character type.
     * @return  A shared pointer to the character.
     */
    std::shared_ptr<AbstractCharacter> loadCharacterType(int theCharType);


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

    /**
     * This opens the database.
     * @param theDbFile This is the dataBase file.
     */
    void openDatabase(const std::string& theDbFile);

    /**
     * This closes the database connection.
     */
    void closeDatabase();

    /**
     * Creates a room table if it doesn't already exist.
     */
    void createRoomTableIfNotExists();

    /**
     * Creates a table for the active characters.
     */
    void createActiveCharacterTableIfNotExists();

    /**
     * Creates a table for character types.
     */
    void createTypeTableIfNotExists();

    /**
     * Saves the room table.
     */
    void saveRoomTable();

    /**
     * Saves the active characters.
     */
    void saveActiveCharacter();

    /**
     * Saves the type table.
     */
    void saveTypeTable();
};

#endif //DATABASEMANAGER_H