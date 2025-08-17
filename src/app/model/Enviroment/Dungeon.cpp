//
// Created by riley on 7/30/25.
//

#include "../../../include/Dungeon.h"
#include "../../../include/NPC.h"




std::unique_ptr<Dungeon> Dungeon::instance = nullptr;



Dungeon* Dungeon::DungeonInstance() {

    //Breaks at this if
    if (instance == nullptr) {
        instance =  std::unique_ptr<Dungeon>(new Dungeon());
    }


    return instance.get();
}


void Dungeon::initialize(const
    std::shared_ptr<DatabaseManager> &dbManager, const std::shared_ptr<Bitz> &bitz) {
    databaseManager = dbManager;
    engine = bitz;
    this->generateDungeon();
}

void Dungeon::generateDungeon() {

    if (!engine) {
        throw std::runtime_error
            ("Bitz is not found");
    }
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

            const auto char1 = NPC::skeletonFactory().get();
            const auto char2 = NPC::skeletonFactory().get();
            const auto char3 = NPC::skeletonFactory().get();

            roomBuilder.setChar1ID(char1->getID());
            roomBuilder.setChar2ID(char2->getID());
            roomBuilder.setChar3ID(char3->getID());

            Bitz::registerCharacter(char1);
            Bitz::registerCharacter(char2);
            Bitz::registerCharacter(char3);

            auto room = roomBuilder.build();
            //This will build the room and throw it in the database.
            try {
                databaseManager->insertRoom(*room);
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
    long long char1 = currentRoom->getCharacters().at(0);
    long long char2 = currentRoom->getCharacters().at(1);
    long long char3 = currentRoom->getCharacters().at(2);

    //This should, set all the npcs in the current room active
    //and deactivate all non-active NPCs.
    for (auto* c: entities) {
        if (NPC* npc = dynamic_cast<NPC*>(c)) {
            if (npc->getID() == char1) npc->setIsActive(true);
            else if (npc->getID() == char2) npc->setIsActive(true);
            else if (npc->getID() == char3) npc->setIsActive(true);
            else npc->setIsActive(false);
        }
    }
}


std::vector<std::vector<int>> Dungeon::getMap() {
    return idMap;

}


std::shared_ptr<Room> Dungeon::getCurrentRoom() {
    return currentRoom;
}


Dungeon::Dungeon() {}


