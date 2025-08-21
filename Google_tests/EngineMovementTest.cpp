//
// Created by RileyHop1 on 8/21/2025.
//


#include "../src/app/model/Characters/Dummy.h"
#include "../src/include/Clock.h"
#include "gtest/gtest.h"

TEST(EngineMovementTest, TestMovementNorth) {
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

    int aroundTheMiddle = 700;

    player->setX(aroundTheMiddle);
    player->setY(aroundTheMiddle);

    player->userInput(SDL_SCANCODE_S);

    Clock::StopClockForTesting(5);
    Clock::runClock();



    ASSERT_TRUE(aroundTheMiddle < player->getY());
}

TEST(EngineMovementTest, TestMovementSouth) {
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

    int aroundTheMiddle = 700;

    player->setX(aroundTheMiddle);
    player->setY(aroundTheMiddle);

    player->userInput(SDL_SCANCODE_W);

    Clock::StopClockForTesting(5);
    Clock::runClock();



    ASSERT_TRUE(aroundTheMiddle > player->getY());
}

TEST(EngineMovementTest, TestMovementEast) {
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

    int aroundTheMiddle = 700;

    player->setX(aroundTheMiddle);
    player->setY(aroundTheMiddle);

    player->userInput(SDL_SCANCODE_D);

    Clock::StopClockForTesting(5);
    Clock::runClock();



    ASSERT_TRUE(aroundTheMiddle < player->getX());

}
TEST(EngineMovementTEst, TestMovementWest) {
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

    int aroundTheMiddle = 700;

    player->setX(aroundTheMiddle);
    player->setY(aroundTheMiddle);

    player->userInput(SDL_SCANCODE_A);

    Clock::StopClockForTesting(5);
    Clock::runClock();



    ASSERT_TRUE(aroundTheMiddle > player->getX());
}