//
// Created by riley on 7/30/25.
//

#include "../../../include/Dungeon.h"





std::unique_ptr<Dungeon> Dungeon::myInstance = nullptr;
std::vector<std::vector<int>> Dungeon::myIdMap{};



Dungeon* Dungeon::DungeonInstance() {

    //Breaks at this if
    if (myInstance == nullptr) {
        myInstance =  std::unique_ptr<Dungeon>(new Dungeon());
    }


    return myInstance.get();
}


void Dungeon::initialize(const std::shared_ptr<DatabaseManager> &theDbManager) {
    databaseManager = theDbManager;
    //Makes sure there isn't any in there at the start.
    Bitz::clearEntities();
    this->myCurrentRoom = myRoomBuilder.build();
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
    Player::playerInstance()->setX((Room::ROOMSIZE * Room::TILESIZE)/2);
    Player::playerInstance()->setY((Room::ROOMSIZE * Room::TILESIZE)/2);

    myIdMap.clear();


    //(row, column) -> (i,j)
    for (int i = 0; i < DUNGEONSIZE; i++) {
        std::vector<int> idRow;
        for (int j = 0; j < DUNGEONSIZE; j++) {

            //Sets the row id somewhere in the thousands.
            int id = DUNGEONIDRANGE + i * ROWINDEXMULT + j;
            myRoomBuilder.setRoomId(id);
            if (i == 0) myRoomBuilder.setRoomNorth(false);
            if (i == DUNGEONSIZE - 1) myRoomBuilder.setRoomSouth(false);
            if (j == 0) myRoomBuilder.setRoomWest(false);
            if (j == DUNGEONSIZE - 1) myRoomBuilder.setRoomEast(false);

            auto char1 = NPC::skeletonFactory();
            //auto char2 = NPC::skeletonFactory();
            //auto char3 = NPC::skeletonFactory();

            myRoomBuilder.setChar1ID(char1->getID());
            //roomBuilder.setChar2ID(char2->getID());
            //roomBuilder.setChar3ID(char3->getID());


            char1->attach(gui);

            Bitz::registerCharacter(char1);
            //Bitz::registerCharacter(char2);
            //Bitz::registerCharacter(char3);

            auto room = myRoomBuilder.build();

            //This will build the room and throw it in the database.
            try {
                databaseManager->insertRoom(*room);
            }catch (std::runtime_error &e) {
                std::cerr << "Failed to insert room: "
                    << e.what() << std::endl;
            }

            idRow.push_back(id);

        }
        myIdMap.push_back(idRow);
    }

    //This will set up the pilers in the dungeon.
    generatePilers();
    //Will randomly spawn potions.
    spawnPotions();
    //Its 100, just so you don't have to look.
    setCharacterRoom(STARTINGROOMID);


}



bool Dungeon::setCharacterRoom(const int theRoomID) {

    if (!roomIDIsInTheDungeon(theRoomID)) {
        return false;

    }

    myCurrentRoom->setSerialRoomMap("");
    myCurrentRoom = databaseManager->loadRoom(theRoomID);
    myCurrentRoom->generateExistingRoom();

    // You win the game by finding all the pilers and destroying them.
    if (myOopPillars.contains(theRoomID)) {
        std::cout << "You found: " << myOopPillars[theRoomID] << std::endl;
        myOopPillars.erase(theRoomID);
        this->notify(PROPERTY_PILLAR_DESTROYED);
    } if (myOopPillars.empty()) {
        std::cout << "All pillars have been destroyed!" << std::endl;
        myWin = true;
        // Trigger a property change for winning, if applicable
        this->notify(PROPERTY_WIN);
    } if (myPotionLocations.contains(theRoomID)) {
        Player::playerInstance()->givePotion();
        myPotionLocations.erase(theRoomID);
    }


    updateRoomEntities(Bitz::getEntities());



    this->notify(PROPERTY_ROOM_CHANGE);

    return true;


}

void Dungeon::updateRoomEntities(std::unordered_set<std::shared_ptr<AbstractCharacter>> theEntities) {
    long long char1 = myCurrentRoom->getCharacters().at(0);
    //long long char2 = currentRoom->getCharacters().at(1);
    //long long char3 = currentRoom->getCharacters().at(2);



    //This should, set all the npcs in the current room active
    //and deactivate all non-active NPCs.
    for (auto c: theEntities) {
        if (std::shared_ptr<NPC> npc = std::dynamic_pointer_cast<NPC>(c)) {
            if (npc->getID() == char1) {
                npc->setIsActive(true);
                myActiveCharaceter = npc;
            }
            //else if (npc->getID() == char2) npc->setIsActive(true);
            //else if (npc->getID() == char3) npc->setIsActive(true);
            else npc->setIsActive(false);
        }
    }



}


std::vector<std::vector<int>> Dungeon::getMap() {
    return myIdMap;

}


std::shared_ptr<Room> Dungeon::getCurrentRoom() {
    return myCurrentRoom;
}


std::shared_ptr<AbstractCharacter> Dungeon::getActiveCharacter() {
    return myActiveCharaceter;
}

Dungeon::Dungeon() {}

bool Dungeon::roomIDIsInTheDungeon(int theId) {
    return std::any_of(myIdMap.begin(), myIdMap.end(), [&](const auto& row) {
        return std::find(row.begin(), row.end(), theId) != row.end();
    });
}

void Dungeon::generatePilers() {

    if (myIdMap.size() != 10) {
        std::cerr << "Error: idMap must have exactly 10 rows!" << std::endl;
        return;
    }
    for (size_t i = 0; i < myIdMap.size(); ++i) {
        if (myIdMap[i].size() != 10) {
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
        int key = myIdMap[dis(gen)][dis(gen)];
        myOopPillars[key] = pillars[i];
    }

}

void Dungeon::printPilerSpawns() {
    if (myOopPillars.empty()) {
        std::cout << "No pillars have been spawned." << std::endl;
        return;
    }

    std::cout << "Current pillar spawns:" << std::endl;
    for (const auto& [id, pillar] : myOopPillars) {
        std::cout << "Room ID: " << id << " -> Pillar: " << pillar << std::endl;
    }
}

void Dungeon::spawnPotions() {
    // Validate map dimensions
    if (myIdMap.size() != 10) {
        std::cerr << "Error: idMap must have exactly 10 rows!\n";
        return;
    }
    for (size_t i = 0; i < myIdMap.size(); ++i) {
        if (myIdMap[i].size() != 10) {
            std::cerr << "Error: Row " << i << " must have exactly 10 elements!\n";
            return;
        }
    }

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> coordDist(0, 9); // for x/y positions
    std::uniform_int_distribution<> potionCountDist(1, 6); // random number of potions

    // Decide how many potions to spawn
    int potionCount = potionCountDist(gen);

    // Clear any previous potion locations
    myPotionLocations.clear();

    for (int i = 0; i < potionCount; ++i) {
        int row = coordDist(gen);
        int col = coordDist(gen);
        int key = myIdMap[row][col];

        // Mark this location as having a potion
        myPotionLocations[key] = true;
    }
}

void Dungeon::destroyPilers() {
    if (myOopPillars.empty()) {
        std::cout << "No pillars to destroy." << std::endl;
        return;
    }

    std::cout << "Destroying pillars..." << std::endl;
    for (const auto& [id, pillar] : myOopPillars) {
        std::cout << "Destroyed pillar " << pillar << " in room " << id << std::endl;
        this->notify(PROPERTY_PILLAR_DESTROYED);
    }

    myOopPillars.clear();

    if (myOopPillars.empty()) {
        std::cout << "All pillars destroyed! You win!" << std::endl;
        myWin = true;
        this->notify(PROPERTY_WIN);
    }
}

bool Dungeon::haveIWon() {
    return myWin;
}

