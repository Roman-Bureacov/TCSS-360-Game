//
// Created by riley on 7/30/25.
//

#include "../../../include/Dungeon.h"





std::unique_ptr<Dungeon> Dungeon::instance = nullptr;



Dungeon* Dungeon::DungeonInstance() {

    //Breaks at this if
    if (instance == nullptr) {
        instance =  std::unique_ptr<Dungeon>(new Dungeon());
    }


    return instance.get();
}


void Dungeon::initialize(const std::shared_ptr<DatabaseManager> &dbManager) {
    databaseManager = dbManager;
    this->currentRoom = roomBuilder.build();
    this->generateDungeon();
}

void Dungeon::generateDungeon() {
    std::shared_ptr<View> gui = View::guiInstance();

    attach(gui);

    if (!databaseManager) {
        throw std::runtime_error
            ("Database manager is not found");
    }
    Bitz::registerPlayer(Player::playerInstance());
    Player::playerInstance()->setX((Room::roomSize * Room::tileSize)/2);
    Player::playerInstance()->setY((Room::roomSize * Room::tileSize)/2);

    idMap.clear();


    //(row, column) -> (i,j)
    for (int i = 0; i < dungeonSize; i++) {
        std::vector<int> idRow;
        for (int j = 0; j < dungeonSize; j++) {

            //Sets the row id somewhere in the thousands.
            int id = dungeonIdRange + i * rowIndexMult + j;
            roomBuilder.setRoomId(id);
            if (i == 0) roomBuilder.setRoomNorth(false);
            if (i == dungeonSize - 1) roomBuilder.setRoomSouth(false);
            if (j == 0) roomBuilder.setRoomWest(false);
            if (j == dungeonSize - 1) roomBuilder.setRoomEast(false);

            auto char1 = NPC::skeletonFactory();
            //auto char2 = NPC::skeletonFactory();
            //auto char3 = NPC::skeletonFactory();

            roomBuilder.setChar1ID(char1->getID());
            //roomBuilder.setChar2ID(char2->getID());
            //roomBuilder.setChar3ID(char3->getID());

            char1->setHitbox( hitBoxSize, hitBoxSize);
            //char2->setHitbox( hitBoxSize, hitBoxSize);
            //char3->setHitbox( hitBoxSize, hitBoxSize);

            char1->attach(gui);

            Bitz::registerCharacter(char1);
            //Bitz::registerCharacter(char2);
            //Bitz::registerCharacter(char3);

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

    //This will set up the pillers in the dungeon
    generatePilers();
    //Its 100, just so you don't have to look.
    setCharacterRoom(startingRoomId);


}



void Dungeon::setCharacterRoom(const int roomID) {

    currentRoom->setSerialRoomMap("");
    currentRoom = databaseManager->loadRoom(roomID);
    currentRoom->generateExistingRoom();

    // You win the game by finding all the pilers and destroying them.
    if (oopPillars.contains(roomID)) {
        std::cout << "You found: " << oopPillars[roomID] << std::endl;
        oopPillars.erase(roomID);
        this->notify(PROPERTY_PILLAR_DESTROYED);
    } if (oopPillars.empty()) {
        std::cout << "All pillars have been destroyed!" << std::endl;
        won = true;
        // Trigger a property change for winning, if applicable
        this->notify(PROPERTY_WIN);
    }


    updateRoomEntities(Bitz::getEntities());



    this->notify(PROPERTY_ROOM_CHANGE);


}

void Dungeon::updateRoomEntities(std::unordered_set<std::shared_ptr<AbstractCharacter>> entities) {
    long long char1 = currentRoom->getCharacters().at(0);
    //long long char2 = currentRoom->getCharacters().at(1);
    //long long char3 = currentRoom->getCharacters().at(2);



    //This should, set all the npcs in the current room active
    //and deactivate all non-active NPCs.
    for (auto c: entities) {
        if (std::shared_ptr<NPC> npc = std::dynamic_pointer_cast<NPC>(c)) {
            if (npc->getID() == char1) {
                npc->setIsActive(true);
                activeCharaceter = npc;
            }
            //else if (npc->getID() == char2) npc->setIsActive(true);
            //else if (npc->getID() == char3) npc->setIsActive(true);
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


std::shared_ptr<AbstractCharacter> Dungeon::getActiveCharacter() {
    return activeCharaceter;
}

Dungeon::Dungeon() {}

void Dungeon::generatePilers() {

    if (idMap.size() != 10) {
        std::cerr << "Error: idMap must have exactly 10 rows!" << std::endl;
        return;
    }
    for (size_t i = 0; i < idMap.size(); ++i) {
        if (idMap[i].size() != 10) {
            std::cerr << "Error: Row " << i << " must have exactly 10 elements!" << std::endl;
            return ;
        }
    }

    const char* pillars[4] = {"Encapsulation", "Abstraction"
        , "Inheritance", "Polymorphism"};


    //random nums form 1 to 9
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    for (int i = 0; i < 4; ++i) {
        int key = idMap[dis(gen)][dis(gen)];
        oopPillars[key] = pillars[i];
    }

}

void Dungeon::printPilerSpawns() {
    if (oopPillars.empty()) {
        std::cout << "No pillars have been spawned." << std::endl;
        return;
    }

    std::cout << "Current pillar spawns:" << std::endl;
    for (const auto& [id, pillar] : oopPillars) {
        std::cout << "Room ID: " << id << " -> Pillar: " << pillar << std::endl;
    }
}

void Dungeon::destroyPilers() {
    if (oopPillars.empty()) {
        std::cout << "No pillars to destroy." << std::endl;
        return;
    }

    std::cout << "Destroying pillars..." << std::endl;
    for (const auto& [id, pillar] : oopPillars) {
        std::cout << "Destroyed pillar " << pillar << " in room " << id << std::endl;
        this->notify(PROPERTY_PILLAR_DESTROYED);
    }

    oopPillars.clear();

    if (oopPillars.empty()) {
        std::cout << "All pillars destroyed! You win!" << std::endl;
        won = true;
        this->notify(PROPERTY_WIN);
    }
}

bool Dungeon::haveIWon() {
    return won;
}

