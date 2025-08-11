//
// Created by riley on 7/30/25.
//

#ifndef DUNGEON_H
#define DUNGEON_H




#include "Room.h"
#include "ObserverPattern.h"
#include <vector>


/*
 * This uses the singleton pattern, there really should only be one
 * Dungeon in memory at a time, we should be grabbing different dungeons.
 */


class Dungeon final : public Subject {
public:

    static Dungeon* DungeonInstance();

    /*
     * I'm thinking that room ids will start in the 100's
     * the tens place will be rows, and the ones columns.
     * I'm starting it in the 100's just because that's kinda like its own area.
     */
    void generateDungeon();
    std::vector<std::vector<int>> getMap();
    std::shared_ptr<Room> getCurrentRoom();

    void setCharacterRoom(int roomID);

private:
    Dungeon();
    ConcreteRoomBuilder roomBuilder;
    //This is basically a placeholder room before, dungeon generation
    std::shared_ptr<Room> currentRoom = roomBuilder.build();
    std::vector<std::vector<int>> idMap;

    static Dungeon* instance;

    //Could possibly make it some people can choose dungeon size, but Ids.
    //Would be More complex.
    const int dungeonSize = 10;
    const int dungeonIdRange = 100;
    const int rowIndexMult = 100;
    const int startingRoomId = 100;

};





#endif //DUNGEON_H
