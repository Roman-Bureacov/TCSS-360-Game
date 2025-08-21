//
// Created by riley on 7/30/25.
//

#ifndef DUNGEON_H
#define DUNGEON_H


#include <unordered_set>
#include <vector>
#include <iostream>
#include <map>
#include <map>
#include <random>
#include <string>

#include "Room.h"
#include "ObserverPattern.h"
#include "DatabaseManager.h"
#include "Bitz.h"
#include "NPC.h"
#include "Player.h"
#include "View.h"

class DatabaseManager;

/**
 * Represents the dungeon system in the game.
 * Manages room generation, navigation, and entity persistence.
 * Implements the singleton pattern and observer notifications.
 *
 * @author Riley Hopper
 * @version July 2025
 */
class Dungeon final : public Subject {
public:
    /**
     * Retrieves the singleton instance of the dungeon.
     * @return Pointer to the Dungeon instance.
     */
    static Dungeon* DungeonInstance();

    /**
     * Initializes the dungeon with a database manager.
     * Sets up internal state and prepares room generation.
     * @param dbManager Shared pointer to the database manager.
     */
    void initialize(const std::shared_ptr<DatabaseManager>& dbManager);

    /**
     * Generates the dungeon layout and rooms.
     * Populates the internal ID map.
     */
    void generateDungeon();

    /**
     * Retrieves the dungeon's room ID map.
     * @return 2D vector of room IDs.
     */
    std::vector<std::vector<int>> getMap();

    /**
     * Gets the current room the player is in.
     * @return Shared pointer to the current room.
     */
    std::shared_ptr<Room> getCurrentRoom();

    /**
     * Changes the current room based on room ID.
     * Triggers a "Room Changed" event.
     * @param roomID ID of the room to switch to.
     */
    void setCharacterRoom(int roomID);

    /**
     * Updates persistent storage with the current room's entities.
     * @param entities Set of characters present in the room.
     */
    void updateRoomEntities(std::unordered_set<std::shared_ptr<AbstractCharacter>> entities);

    /**
     * This prints the Spawn locations of the pilers for testing.
     */
    void printPilerSpawns();

    /**
     * Destroys all pilers for testing.
     */
    void destroyPilers();

    /**
     * This is the getter for the won boolean.
     * @return This is the truthy value of if you won.
     */
    bool haveIWon();

    /** Property name used to signal room change events. */
    inline static const std::string PROPERTY_ROOM_CHANGE = "Room Changed";
    /**Property change for will the player wins the game. */
    inline static const std::string PROPERTY_WIN = "Game Won";
    /**Property change for when a piler is destroyed. */
    inline static const std::string PROPERTY_PILLAR_DESTROYED = "Pillar Destroyed";


    /**
     *
     * @return Gets the active character within the room.
     */
    std::shared_ptr<AbstractCharacter> getActiveCharacter();

private:
    /** Constructs the Dungeon object. Private for singleton enforcement. */
    Dungeon();

    /**
     * Places the pilers in random locations,
     * Within the dungeon.
     */
    void generatePilers();

    /** Builder used to construct rooms. */
    ConcreteRoomBuilder roomBuilder;

    /** Pointer to the current room the player occupies. */
    std::shared_ptr<Room> currentRoom;

    /** 2D map of room IDs representing the dungeon layout. */
    std::vector<std::vector<int>> idMap;

    /** Singleton instance of the dungeon. */
    static std::unique_ptr<Dungeon> instance;

    /** Database manager used for persistence and loading. */
    std::shared_ptr<DatabaseManager> databaseManager;

    /** Size of the dungeon grid (10x10 rooms). */
    const int dungeonSize = 10;

    /** Starting ID value for room generation. */
    const int dungeonIdRange = 100;

    /** Multiplier used to calculate unique room IDs by row. */
    const int rowIndexMult = 100;

    /** ID of the room where the player spawns. */
    const int startingRoomId = 100;

    /**This is the active character.*/
    std::shared_ptr<AbstractCharacter> activeCharaceter;

    /**This is a map of pilers locations*/
    std::map<int, std::string> oopPillars;

    /**This is if the player has beat the dungeon.*/
    bool won = false;


};






#endif //DUNGEON_H
