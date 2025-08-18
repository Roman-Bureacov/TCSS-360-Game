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

    ASSERT_EQ(Bitz::getEntities().size(), 300);



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

        if (npc->getIsActive()) {
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

        if (npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }

    int initalX = allNPCs[0]->getX();
    int initalY = allNPCs[0]->getY();

    Clock::StopClockForTesting( 10 * Clock::getTickRate());
    Clock::runClock();

    int endX = allNPCs[0]->getX();
    int endY = allNPCs[0]->getY();

    ASSERT_NE(initalX, endX);
    ASSERT_NE(initalY, endY);





}