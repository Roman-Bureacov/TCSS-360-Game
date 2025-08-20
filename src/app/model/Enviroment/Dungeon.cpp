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

            std::shared_ptr<NPC> char1;
            if (1 + (std::rand() % 2) == 1) char1 = NPC::skeletonFactory();
            else char1 = NPC::goblinFactory();



            roomBuilder.setChar1ID(char1->getID());


            char1->setHitbox( hitBoxSize, hitBoxSize);


            char1->attach(gui);

            Bitz::registerCharacter(char1);


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

    currentRoom->setSerialRoomMap("");
    currentRoom = databaseManager->loadRoom(roomID);
    currentRoom->generateExistingRoom();
    updateRoomEntities(Bitz::getEntities());



    this->notify(PROPERTY_ROOM_CHANGE);


}

void Dungeon::updateRoomEntities(std::unordered_set<std::shared_ptr<AbstractCharacter>> entities) {
    long long char1 = currentRoom->getCharacters().at(0);




    //This should, set all the npcs in the current room active
    //and deactivate all non-active NPCs.
    for (auto c: entities) {
        if (std::shared_ptr<NPC> npc = std::dynamic_pointer_cast<NPC>(c)) {
            if (npc->getID() == char1) {
                npc->setIsActive(true);
                activeCharaceter = npc;
            }
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


