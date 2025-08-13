//
// Created by riley on 7/30/25.
//

#include "../../../include/Dungeon.h"

#include <unordered_set>

std::unique_ptr<Dungeon> Dungeon::instance = nullptr;



Dungeon* Dungeon::DungeonInstance() {

    //Breaks at this if
    if (instance == nullptr) {
        instance = std::make_unique<Dungeon>();
    }


    return instance.get();
}


void Dungeon::initialize(const
    std::shared_ptr<DatabaseManager> &dbManager) {
    databaseManager = dbManager;
    this->generateDungeon();
}

void Dungeon::generateDungeon() {

    if (!databaseManager) {
        throw std::runtime_error
            ("Database manager is not found");
    }

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

            auto room = roomBuilder.build();
            //This will build the room and throw it in the database.
            try {
                databaseManager->insertRoom(room);
            }catch (std::runtime_error &e) {
                std::cerr << "Failed to insert room: "
                    << e.what() << std::endl;
            }
            idRow.push_back(id);
        }
        idMap.push_back(idRow);
    }

    //Its 100, just so you don't have to look.
    setCharacterRoom(startingRoomId);


}



void Dungeon::setCharacterRoom(const int roomID) {
    currentRoom = databaseManager->loadRoom(roomID);

    this->notify(PROPERTY_ROOM_CHANGE);
}

void Dungeon::updateRoomEntities(std::unordered_set<AbstractCharacter *> entities) {
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


