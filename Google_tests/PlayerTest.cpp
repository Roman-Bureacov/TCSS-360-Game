//
// Created by riley on 8/18/25.
//

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "../src/include/Dungeon.h"
#include "../src/include/NPC.h"
#include "../src/include/Player.h"

TEST(PLAYERTEST,movementEastTest) {
    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    dungeon->setCharacterRoom(300);

    auto room = dungeon->getCurrentRoom();

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }


    auto player = Player::playerInstance();
    allNPCs[0]->setIsActive(false);
    allNPCs[1]->setIsActive(false);
    allNPCs[2]->setIsActive(false);


    SDL_Event event;
    event.type = SDL_EVENT_KEY_DOWN;
    event.key.scancode = SDL_SCANCODE_D;

    //I'm too tired to write a getter.
    int finalX = player->getX() + 75;
    int finalY = player->getY();

    int initialX = player->getX();
    int initialY = player->getY();


    player->userInput(event);


}
