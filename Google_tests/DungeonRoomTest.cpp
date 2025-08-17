//
// Created by riley on 8/17/25.
//
#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "../src/include/Dungeon.h"


/**Helper method for dungeon room ids*/
std::vector<std::vector<int>> expectedDungeonIds() {
    return {
            { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 },
            { 200, 201, 202, 203, 204, 205, 206, 207, 208, 209 },
            { 300, 301, 302, 303, 304, 305, 306, 307, 308, 309 },
            { 400, 401, 402, 403, 404, 405, 406, 407, 408, 409 },
            { 500, 501, 502, 503, 504, 505, 506, 507, 508, 509 },
            { 600, 601, 602, 603, 604, 605, 606, 607, 608, 609 },
            { 700, 701, 702, 703, 704, 705, 706, 707, 708, 709 },
            { 800, 801, 802, 803, 804, 805, 806, 807, 808, 809 },
            { 900, 901, 902, 903, 904, 905, 906, 907, 908, 909 },
            {1000,1001,1002,1003,1004,1005,1006,1007,1008,1009 }
    };
}


TEST(DungeonRoom, RoomIDsMatch) {
    auto expected = expectedDungeonIds();

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    auto actual = dungeon->getMap();

    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(actual[i].size(), expected[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j) {
            EXPECT_EQ(actual[i][j], expected[i][j])
                << "Mismatch at (" << i << "," << j << ")";
        }
    }


}

TEST(DungeonRoom, instanceWorks) {
    Dungeon* dungeon1 = Dungeon::DungeonInstance();
    Dungeon* dungeon2 = Dungeon::DungeonInstance();

    // Check that both pointers are equal — same instance
    EXPECT_EQ(dungeon1, dungeon2) << "DungeonInstance() did not return the same singleton";

    // Optional: check that it's non-null
    ASSERT_NE(dungeon1, nullptr) << "DungeonInstance() returned null";
}


TEST(DungeonRoom, MultipleloadRoomWorks) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);
    dungeon->setCharacterRoom(100);
    dungeon->setCharacterRoom(1000);
    dungeon->setCharacterRoom(109);
    dungeon->setCharacterRoom(1009);
    dungeon->setCharacterRoom(205);

    const std::string expected =
            "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VD,F,F,F,F,F,F,F,F,F,F,F,F,F,VD;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "SWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,SEC;";

    EXPECT_EQ(dungeon->getCurrentRoom()->getSerialRoomMap(), expected);



}

TEST(DungeonRoom, loadRoomWorksMiddle) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);
    dungeon->setCharacterRoom(205);

    const std::string expected =
            "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VD,F,F,F,F,F,F,F,F,F,F,F,F,F,VD;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "SWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,SEC;";

   EXPECT_EQ(dungeon->getCurrentRoom()->getSerialRoomMap(), expected);



}

TEST(DungeonRoom, loadRoomWorksBottomRight) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);
    dungeon->setCharacterRoom(1009);

    const std::string expected =
            "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VD,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "SWC,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,SEC;";

    EXPECT_EQ(dungeon->getCurrentRoom()->getSerialRoomMap(), expected);



}

TEST(DungeonRoom, loadRoomWorksTopRight) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);
    dungeon->setCharacterRoom(109);

    const std::string expected =
            "NWC,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,NEC;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VD,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "SWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,SEC;";

    EXPECT_EQ(dungeon->getCurrentRoom()->getSerialRoomMap(), expected);



}

TEST(DungeonRoom, loadRoomWorksBottomLeft) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);
    dungeon->setCharacterRoom(1000);

    const std::string expected =
            "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VD;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
            "SWC,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,SEC;";

    EXPECT_EQ(dungeon->getCurrentRoom()->getSerialRoomMap(), expected);



}

TEST(DungeonRoom, loadRoomWorksTopLeft) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);
    dungeon->setCharacterRoom(100);

    const std::string expected =
        "NWC,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,NEC;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VD;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "SWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,SEC;";

    EXPECT_EQ(dungeon->getCurrentRoom()->getSerialRoomMap(), expected);



}



TEST(RoomTileGeneration, FourDoors) {
    auto room = ConcreteRoomBuilder()
        .setRoomWest(true).setRoomSouth(true)
        .setRoomNorth(true).setRoomEast(true)
        .build();

    const std::string expected =
        "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VD,F,F,F,F,F,F,F,F,F,F,F,F,F,VD;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "SWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,SEC;";

    SCOPED_TRACE("FourDoors");
    EXPECT_EQ(room->getSerialRoomMap(), expected);
}

TEST(RoomTileGeneration, ThreeDoorsEWS) {
    auto room = ConcreteRoomBuilder()
        .setRoomWest(true).setRoomSouth(true)
        .setRoomNorth(false).setRoomEast(true)
        .build();

    const std::string expected =
        "NWC,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,NEC;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VD,F,F,F,F,F,F,F,F,F,F,F,F,F,VD;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "SWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,SEC;";

    SCOPED_TRACE("ThreeDoorsEWS");
    EXPECT_EQ(room->getSerialRoomMap(), expected);
}

TEST(RoomTileGeneration, ThreeDoorsEWN) {
    auto room = ConcreteRoomBuilder()
        .setRoomWest(true).setRoomSouth(false)
        .setRoomNorth(true).setRoomEast(true)
        .build();

    const std::string expected =
        "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VD,F,F,F,F,F,F,F,F,F,F,F,F,F,VD;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "SWC,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,SEC;";

    SCOPED_TRACE("ThreeDoorsEWN");
    EXPECT_EQ(room->getSerialRoomMap(), expected);
}

TEST(RoomTileGeneration, ThreeDoorsENS) {
    auto room = ConcreteRoomBuilder()
        .setRoomWest(false).setRoomSouth(true)
        .setRoomNorth(true).setRoomEast(true)
        .build();

    const std::string expected =
        "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VD;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "SWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,SEC;";

    SCOPED_TRACE("ThreeDoorsENS");
    EXPECT_EQ(room->getSerialRoomMap(), expected);
}

TEST(RoomTileGeneration, ThreeDoorsSNW) {
    auto room = ConcreteRoomBuilder()
        .setRoomWest(true).setRoomSouth(true)
        .setRoomNorth(true).setRoomEast(false)
        .build();

    const std::string expected =
        "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VD,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "VW,F,F,F,F,F,F,F,F,F,F,F,F,F,VW;"
        "SWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,SEC;";

    SCOPED_TRACE("ThreeDoorsWNS");
    EXPECT_EQ(room->getSerialRoomMap(), expected);
}

