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
     * @param theDbManager Shared pointer to the database manager.
     */
    void initialize(const std::shared_ptr<DatabaseManager>& theDbManager);

    /**
     * Generates the dungeon layout and rooms.
     * Populates the internal ID map.
     */
    void generateDungeon();

    /**
     * Retrieves the dungeon's room ID map.
     * @return 2D vector of room IDs.
     */
    static std::vector<std::vector<int>> getMap();

    /**
     * Gets the current room the player is in.
     * @return Shared pointer to the current room.
     */
    std::shared_ptr<Room> getCurrentRoom();

    /**
     * Changes the current room based on room ID.
     * Triggers a "Room Changed" event.
     * @param theRoomID ID of the room to switch to.
     * @return truthy value related to if the room could be set.
     */
    bool setCharacterRoom(int theRoomID);

    /**
     * Updates persistent storage with the current room's entities.
     * @param theEntities Set of characters present in the room.
     */
    void updateRoomEntities(const std::unordered_set<std::shared_ptr<AbstractCharacter>> &theEntities);

    /**
     * This prints the Spawn locations of the pilers for testing.
     */
    void printPilerSpawns();

    /**
     * This spawns potions.
     */
    void spawnPotions();

    /**
     * Destroys all pilers for testing.
     */
    void destroyPilers();

    /**
     * This will set some traps in
     * the dungeon rooms.
     */
    void setUpTrappedRooms();

    /**
     * This will check if the room has a piler, has a potion, has
     * a trap and such in it and apply the according affects of those
     * interactions.
     * @param theRoomID The room to be checked for the interactable.
     */
    void checkInteractAbles(int theRoomID);
    /**
     * This is the getter for the won boolean.
     * @return This is the truthy value of if you won.
     */
    bool haveIWon() const;

    /** Property name used to signal room change events. */
    inline static const std::string PROPERTY_ROOM_CHANGE = "Room Changed";
    /**Property change for will the player wins the game. */
    inline static const std::string PROPERTY_WIN = "Game Won";
    /**Property change for when a piler is destroyed. */
    inline static const std::string PROPERTY_PILLAR_DESTROYED = "Pillar Destroyed";

    /**This is to the amount that rooms east and west change.*/
    inline static const int ROOMHORIZONTALIDCHANGE = 1;

    /**This is the amount rooms to the north or south change.*/
    inline static const int ROOMVERTICALIDCHANGE = 100;

    /**
     *
     * @return Gets the active character within the room.
     */
    std::shared_ptr<AbstractCharacter> getActiveCharacter();

private:
    /** Constructs the Dungeon object. Private for singleton enforcement. */
    Dungeon();

    /**
     *
     * @param theId This is the room id that will be looked for.
     * @return A truthy value if it exists within the dungeon
     */
    static bool roomIDIsInTheDungeon(int theId);

    /**
     * Places the pilers in random locations,
     * Within the dungeon.
     */
    void generatePilers();

    /** Builder used to construct rooms. */
    ConcreteRoomBuilder myRoomBuilder;

    /** Pointer to the current room the player occupies. */
    std::shared_ptr<Room> myCurrentRoom;

    /** 2D map of room IDs representing the dungeon layout. */
    static std::vector<std::vector<int>> myIdMap;

    /** Singleton instance of the dungeon. */
    static std::unique_ptr<Dungeon> myInstance;

    /** Database manager used for persistence and loading. */
    std::shared_ptr<DatabaseManager> databaseManager;

    /** Size of the dungeon grid (10x10 rooms). */
    static constexpr int DUNGEONSIZE = 10;

    /** Starting ID value for room generation. */
    static constexpr int DUNGEONIDRANGE = 100;

    /** Multiplier used to calculate unique room IDs by row. */
    static constexpr int ROWINDEXMULT = 100;

    /** ID of the room where the player spawns. */
    static constexpr int STARTINGROOMID = 100;

    /**This is the active character.*/
    std::shared_ptr<AbstractCharacter> myActiveCharaceter;

    /**This is a map of pilers locations*/
    std::map<int, std::string> myOopPillars;

    /**This is a map of the potion spawn locations.*/
    std::map<int, bool> myPotionLocations;

    /**This is a map of  what rooms are trapped.*/
    std::map<int, bool> myTrappedRooms;

    /**This is the damage the traps do.*/
    static constexpr int TRAPDAMAGE = 10;


    /**This is if the player has beat the dungeon.*/
    bool myWin = false;


};






#endif //DUNGEON_H
