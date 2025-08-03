//
// Created by riley on 8/3/25.
//



#include "TestRoom.h"



bool TestRoom::TestTileGeneration4Doors() {
    std::shared_ptr<Room> room = ConcreteRoomBuilder()
        .setRoomWest(true).setRoomSouth(true).setRoomNorth(true)
        .setRoomEast(true).build();

    //I had chatgpt generate this string and I swear to god it was awful, the bottom wall was all VWs, and SWC was WC
    std::string fourDoorRoom = "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
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

    if (room->getSerialRoomMap() == fourDoorRoom) {
        std::cout << "TestCase: TestTileGeneration4Doors passed;" << std::endl;
        return true;

    } else {
        std::cout << "TestCase: TestTileGeneration4Doors failed;" << std::endl;
        std::cout << fourDoorRoom << std::endl;
        std::cout << room->getSerialRoomMap() <<std::endl;
        return false;
    }
}

bool TestRoom::TestTileGeneration3DoorsEWS() {
    std::shared_ptr<Room> room = ConcreteRoomBuilder()
        .setRoomWest(true).setRoomSouth(true).setRoomNorth(false)
        .setRoomEast(true).build();

    //I had chatgpt generate this string and I swear to god it was awful, the bottom wall was all VWs, and SWC was WC
    std::string fourDoorRoom = "NWC,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,HW,NEC;"
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

    if (room->getSerialRoomMap() == fourDoorRoom) {
        std::cout << "TestCase: TestTileGeneration3DoorsEWS passed;" << std::endl;
        return true;

    } else {
        std::cout << "TestCase: TestTileGeneration3DoorsEWS failed;" << std::endl;
        std::cout << fourDoorRoom << std::endl;
        std::cout << room->getSerialRoomMap() <<std::endl;
        return false;
    }
}

bool TestRoom::TestTileGeneration3DoorsEWN() {
    std::shared_ptr<Room> room = ConcreteRoomBuilder()
    .setRoomWest(true).setRoomSouth(false).setRoomNorth(true)
    .setRoomEast(true).build();

    //I had chatgpt generate this string and I swear to god it was awful, the bottom wall was all VWs, and SWC was WC
    std::string fourDoorRoom = "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
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

    if (room->getSerialRoomMap() == fourDoorRoom) {
        std::cout << "TestCase: TestTileGeneration3DoorsEWS passed;" << std::endl;
        return true;

    } else {
        std::cout << "TestCase: TestTileGeneration3DoorsEWS failed;" << std::endl;
        std::cout << fourDoorRoom << std::endl;
        std::cout << room->getSerialRoomMap() <<std::endl;
        return false;
    }
}

bool TestRoom::TestTileGeneration3DoorsENS() {
    std::shared_ptr<Room> room = ConcreteRoomBuilder()
        .setRoomWest(false).setRoomSouth(true).setRoomNorth(true)
        .setRoomEast(true).build();

    //I had chatgpt generate this string and I swear to god it was awful, the bottom wall was all VWs, and SWC was WC
    std::string fourDoorRoom = "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
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

    if (room->getSerialRoomMap() == fourDoorRoom) {
        std::cout << "TestCase: TestTileGeneration3DoorsENS passed;" << std::endl;
        return true;

    } else {
        std::cout << "TestCase: TestTileGeneration3DoorsENS failed;" << std::endl;
        std::cout << fourDoorRoom << std::endl;
        std::cout << room->getSerialRoomMap() <<std::endl;
        return false;
    }
}


bool TestRoom::TestTileGeneration3DoorsSNW() {
    std::shared_ptr<Room> room = ConcreteRoomBuilder()
    .setRoomWest(true).setRoomSouth(true).setRoomNorth(true)
    .setRoomEast(false).build();

    //I had chatgpt generate this string and I swear to god it was awful, the bottom wall was all VWs, and SWC was WC
    std::string fourDoorRoom = "NWC,HW,HW,HW,HW,HW,HW,HD,HW,HW,HW,HW,HW,HW,NEC;"
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

    if (room->getSerialRoomMap() == fourDoorRoom) {
        std::cout << "TestCase: TestTileGeneration4Doors passed;" << std::endl;
        return true;

    } else {
        std::cout << "TestCase: TestTileGeneration4Doors failed;" << std::endl;
        std::cout << fourDoorRoom << std::endl;
        std::cout << room->getSerialRoomMap() <<std::endl;
        return false;
    }

}

