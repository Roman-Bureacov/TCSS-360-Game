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

    static Dungeon DungeonInstance();

    std::vector<std::vector<Room*>> generateDungeon();
    std::vector<std::vector<int>> getMap();

    Room setCharacterRoom(int roomID);




private:

    Dungeon();
    Room currentRoom;
    std::vector<std::vector<int>> idMap;

};



#endif //DUNGEON_H
