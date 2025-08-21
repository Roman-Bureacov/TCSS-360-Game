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


class NPC;
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
    * Inserts or updates an active NPC instance in the database.
    * Stores the NPC's type, current room, health, position, and active state.
    *
    * @param theCharacter Reference to the NPC to be inserted or updated.
    *        Must be an instance of NPC or a derived class.
    */
    void insertCharacter(AbstractCharacter &theCharacter) const;

    /**
     * Loads all NPC instances for a given room from the database.
     * Uses the stored type_id to construct the correct NPC subclass
     * with base stats from NPCStats, then applies saved instance state.
     *
     * @param theRoomId The ID of the room whose NPCs should be loaded.
     * @return A vector of shared pointers to NPC objects for that room.
     */
    std::vector<std::shared_ptr<NPC>> loadCharacters(int theRoomId);

    /**
     * Creates an NPC of the given type with base stats from NPCStats.
     * This does not set instance-specific state like position or health.
     *
     * @param theCharType The NPC type ID (matches NPCType enum).
     * @return A shared pointer to a newly constructed NPC of the given type.
     */
    std::shared_ptr<NPC> loadCharacterType(int theCharType);


    /**
    * This loads a room from the database.
    * @param theId this is the id of the room to be loaded.
    * @return This is a smart pointer to the room.
    */
    std::shared_ptr<Room> loadRoom(int theId);



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
    * Creates the table for storing active NPC instances if it does not exist.
    * The table stores NPC type, room, health, position, and active state.
    */
    void createActiveNPCTableIfNotExists();


};

#endif//DATABASEMANAGER_H