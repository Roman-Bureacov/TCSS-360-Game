//
// Created by riley on 7/30/25.
//

#ifndef DUNGEON_H
#define DUNGEON_H




#include "Room.h"
#include "ObserverPattern.h"
#include "DatabaseManager.h"
#include <vector>
#include <iostream>



class Dungeon final : public Subject {
public:

    /**
     * This controls the amount of dungeons, for the singleton pattern.
     * @return Returns a pointer to the dungeon instance.
     */
    static Dungeon* DungeonInstance();

    /**
    * Does all the setup for the dungeon.
    * @param dbManager This is a pointer to the database
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

private:
    /**
     * Constructs the object.
     */
    Dungeon();
    ConcreteRoomBuilder roomBuilder;
    std::shared_ptr<Room> currentRoom;
    std::vector<std::vector<int>> idMap;

    static std::unique_ptr<Dungeon> instance;
    std::shared_ptr<DatabaseManager> databaseManager;

    //Could possibly make it some people can choose dungeon size, but Ids.
    //Would be More complex.
    const int dungeonSize = 10;
    const int dungeonIdRange = 100;
    const int rowIndexMult = 10;
    const int startingRoomId = 100;

    //These are the property changes events
    inline static const std::string PROPERTY_ROOM_CHANGE = "Room Changed";

};





#endif //DUNGEON_H
