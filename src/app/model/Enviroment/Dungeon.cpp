//
// Created by riley on 7/30/25.
//

#include "../../../include/Dungeon.h"

#include <unordered_set>

Dungeon* Dungeon::instance = 0;


Dungeon* Dungeon::DungeonInstance() {

    //Breaks at this if
    if (instance == 0) {
        instance = new Dungeon();
    }


    return instance;
}

void Dungeon::generateDungeon() {


    //(row, column) -> (i,j)
    for (int i = 0; i < dungeonSize; i++) {
        std::vector<int> idRow;
        for (int j = 0; j < dungeonSize; j++) {
            //Sets the row id somewhere in the hundreds.
            int id = dungeonIdRange + i * rowIndexMult + j;
            roomBuilder.setRoomId(id);
            if (i == 0) roomBuilder.setRoomNorth(false);
            if (i == dungeonSize - 1) roomBuilder.setRoomSouth(false);
            if (j == 0) roomBuilder.setRoomWest(false);
            if (j == dungeonSize - 1) roomBuilder.setRoomEast(false);
            roomBuilder.setGenerated(false);
            roomBuilder.build();
            idRow.push_back(id);
        }
        idMap.push_back(idRow);
    }

    //Its 100, just so you don't have to look.
    setCharacterRoom(startingRoomId);


}



void Dungeon::setCharacterRoom(int roomID) {
    //Going to need to learn SQL for this bugger right here.
    //This is going to load the rooms data from the database.

}

void Dungeon::updateRoom(std::unordered_set<AbstractCharacter *> entities) {
    // TODO: database implementation
}

std::vector<std::vector<int>> Dungeon::getMap() {
    return idMap;

}

std::shared_ptr<Room> Dungeon::getCurrentRoom() {
    return currentRoom;
}


Dungeon::Dungeon() {
    this->generateDungeon();

}


