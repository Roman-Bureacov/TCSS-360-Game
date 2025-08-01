//
// Created by riley on 7/30/25.
//

#include "../../../include/Dungeon.h"

std::unique_ptr<Dungeon> Dungeon::dungeonInstance = nullptr;


Dungeon* Dungeon::DungeonInstance() {

    if (!dungeonInstance) {
        dungeonInstance = std::make_unique<Dungeon>();

    }

    return dungeonInstance.get();
}

std::vector<std::vector<std::shared_ptr<Room>>> Dungeon::generateDungeon() {
    std::vector<std::vector<std::shared_ptr<Room>>> dungeon;

    //(row, column) -> (i,j)
    for (int i = 0; i < dungeonSize; i++) {
        std::vector<std::shared_ptr<Room>> row;
        for (int j = 0; j < dungeonSize; j++) {
            //Sets the row id somewhere in the hundreds.
            roomBuilder.setRoomId(dungeonIdRange + i * rowIndexMult + j);
            if (i == 0) roomBuilder.setRoomNorth(false);
            if (i == dungeonSize - 1) roomBuilder.setRoomSouth(false);
            if (j == 0) roomBuilder.setRoomWest(false);
            if (j == dungeonSize - 1) roomBuilder.setRoomEast(false);
            row.push_back(roomBuilder.build());
        }
        dungeon.push_back(row);
    }

    //Its 100, just so you don't have to look.
    setCharacterRoom(startingRoomId);


    return dungeon;
}



Room Dungeon::setCharacterRoom(int roomID) {
    //Gonna need to learn SQL for this bugger right here.
    //This is going to load the rooms data from the database.

    notify();
}

std::vector<std::vector<int>> Dungeon::getMap() {}

std::shared_ptr<Room> Dungeon::getCurrentRoom() {
    return currentRoom;
}


Dungeon::Dungeon() {
    this->generateDungeon();

}


void DungeonLogger::Update(Subject *subject) {
}

