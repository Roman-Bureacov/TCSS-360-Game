//
// Created by riley on 7/30/25.
//

#ifndef DUNGEON_H
#define DUNGEON_H


#include <unordered_set>
#include <vector>
#include <iostream>

#include "Room.h"
#include "ObserverPattern.h"
#include "DatabaseManager.h"
#include "Bitz.h"
#include "NPC.h"



/**
 * This is the dungeon, it constructs a dungeon, and its rooms.
 *
 * @author Riley Hopper
 * @version July 2025
 */
class Dungeon final : public Subject {
public:

    /**
     * This controls the amount of dungeons, for the singleton pattern.
     * @return Returns a pointer to the dungeon instance.
     */
    static Dungeon* DungeonInstance();

    /**
    * Does all the setup for the dungeon.
    * @param dbManager This is a pointer to the database.
    * @param bitz This is a pointer to the engine.
    */
    void initialize(const std::shared_ptr<DatabaseManager> &dbManager);

    /**
    * Generates the dungeon.
    */
    void generateDungeon();

    /**
     * This returns a map of the ids from the dungeon.
     * @return 2D vector of the dungeons ids.
     */
    std::vector<std::vector<int>> getMap();

    /**
     * This will return the current room on the screen.
     * @return The current room on the screen.
     */
    std::shared_ptr<Room> getCurrentRoom();

    /**
     * This changes the current room on screen.
    * Fires "Room Changed" event.
    * @param roomID room to change to.
    */
    void setCharacterRoom(int roomID);

    /**
     * Updates the state of this room with the new set of entities
     * to set in persistent storage.
     * @param entities the set of entities in this room
     */
    void updateRoomEntities(std::unordered_set<AbstractCharacter*> entities);


private:
    /**Constructs the object.*/
    Dungeon();

    /**This is the room builder for making rooms.*/
    ConcreteRoomBuilder roomBuilder;
    /**A smart pointer to the current room the player is within.*/
    std::shared_ptr<Room> currentRoom;
    /**A map of the dungeon represented as ids.*/
    std::vector<std::vector<int>> idMap;

    /**This is the dungeons instance.*/
    static std::unique_ptr<Dungeon> instance;
    /**This is the databaseManager object the dungeon will use.*/
    std::shared_ptr<DatabaseManager> databaseManager;

    /**This is the size of the dungeon, 10 rooms by 10 rooms*/
    const int dungeonSize = 10;
    /**This is the starting id value*/
    const int dungeonIdRange = 100;
    /**Rows increase by 100 columns by 1, this will create unique ids for each room.*/
    const int rowIndexMult = 100;
    /**This is the id of the players spawn room*/
    const int startingRoomId = 100;

    /**This is a room changed property changed event*/
    inline static const std::string PROPERTY_ROOM_CHANGE = "Room Changed";

};





#endif //DUNGEON_H
