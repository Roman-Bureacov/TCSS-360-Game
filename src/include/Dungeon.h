//
// Created by riley on 7/30/25.
//

#ifndef DUNGEON_H
#define DUNGEON_H


#include "Room.h"
#include <vector>

/*
 * This uses the singleton pattern, there really should only be one
 * Dungeon in memory at a time, we should be grabbing different dungeons.
 */


class Dungeon {
public:

    static Dungeon* DungeonInstance();


    /*
     * I'm thinking that room ids will start in the 100's
     * the tens place will be rows, and the ones columns.
     * I'm starting it in the 100's just because that's kinda like its own area.
     */
    std::vector<std::vector<std::shared_ptr<Room>>> generateDungeon();
    std::vector<std::vector<int>> getMap();

    Room setCharacterRoom(int roomID);




private:
    ConcreteRoomBuilder roomBuilder;

    static std::unique_ptr<Dungeon> dungeonInstance;

    Dungeon();
    //This is basically a placeholder room before, dungeon generation
    std::shared_ptr<Room> currentRoom = roomBuilder.build();
    std::vector<std::vector<int>> idMap;

    //Could possibly make it some people can choose dungeon size, but Ids.
    //Would be More complex.
    const int dungeonSize = 10;
    const int dungeonIdRange = 100;
    const int rowIndexMult = 10;

};



#endif //DUNGEON_H
