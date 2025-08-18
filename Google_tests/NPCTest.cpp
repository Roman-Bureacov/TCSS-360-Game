//
// Created by riley on 8/17/25.
//

#include <string>
#include <memory>

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