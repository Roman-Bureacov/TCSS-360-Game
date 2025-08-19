//
// Created by riley on 8/17/25.
//

#include <string>
#include <memory>

#include "../src/include/Clock.h"
#include "gtest/gtest.h"
#include "../src/include/Dungeon.h"
#include "../src/include/NPC.h"


TEST(NPCTEST, SpawnTest) {



    int NotExpected = 0;
    int testLength = 1000;

    for (int i = 0; i < testLength; i++) {
        auto skeleton = NPC::skeletonFactory();
        auto skeleton2 = NPC::skeletonFactory();



        int yActual = skeleton->getY();
        int xActual = skeleton->getX();

        ASSERT_TRUE(yActual > NotExpected);
        ASSERT_TRUE(xActual > NotExpected);

        ASSERT_TRUE(yActual < Room::roomSize * Room::tileSize);
        ASSERT_TRUE(xActual < Room::roomSize * Room::tileSize);


    }
}



TEST(NPCTEST,DungeonSpawnsNPCTest) {

    ASSERT_EQ(Bitz::getEntities().size(), 0);

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    auto room = dungeon->getCurrentRoom();

    //300 npcs and 1 player.
    ASSERT_EQ(Bitz::getEntities().size(), 301);



}

TEST(NPCTEST, ActiveNPCs) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    //Changing rooms an random number of times.
    dungeon->setCharacterRoom(309);
    dungeon->setCharacterRoom(303);
    dungeon->setCharacterRoom(304);
    dungeon->setCharacterRoom(305);
    dungeon->setCharacterRoom(306);
    dungeon->setCharacterRoom(307);
    dungeon->setCharacterRoom(308);

    auto room = dungeon->getCurrentRoom();

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }
    ASSERT_EQ(allNPCs.size(), 3);

}

TEST(NPCTEST,GoToPLayer) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    dungeon->setCharacterRoom(300);

    auto room = dungeon->getCurrentRoom();

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if ( npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }
    auto player = Player::playerInstance();


    int initalX1 = allNPCs[0]->getX();
    int initalY1 = allNPCs[0]->getY();

    int initalX2 = allNPCs[1]->getX();
    int initalY2 = allNPCs[1]->getY();

    int initalX3 = allNPCs[2]->getX();
    int initalY3 = allNPCs[2]->getY();


   Clock::StopClockForTesting( 5);
    Clock::runClock();

    int endX1 = allNPCs[0]->getX();
    int endY1 = allNPCs[0]->getY();

    int endX2 = allNPCs[1]->getX();
    int endY2 = allNPCs[1]->getY();

    int endX3 = allNPCs[2]->getX();
    int endY3 = allNPCs[2]->getY();

    ASSERT_TRUE(initalX1 != endX1 || initalY1 != endY1);
    ASSERT_TRUE(initalX2 != endX2 || initalY2 != endY2);
    ASSERT_TRUE(initalX3 != endX3 || initalY3 != endY3);





}

TEST(NPCTEST, AttackPLayer) {
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
    allNPCs[1]->setIsActive(false);
    allNPCs[2]->setIsActive(false);

    int playerHealth = player->getHealth();

    Clock::StopClockForTesting( 25);
    Clock::runClock();

    ASSERT_NE(playerHealth, player->getHealth());


}

TEST(NPCTEST, NPCDEATH) {
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
    allNPCs[0]->setHealth(0);
    allNPCs[1]->setHealth(-1);

    Clock::StopClockForTesting(5);
    Clock::runClock();

    ASSERT_FALSE(allNPCs[0]->getIsActive());
    ASSERT_FALSE(allNPCs[1]->getIsActive());
    ASSERT_TRUE(allNPCs[2]->getIsActive());



}