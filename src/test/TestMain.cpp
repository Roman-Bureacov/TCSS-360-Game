//
// Created by riley on 8/3/25.
//

#include "TestRoom.h"
#include "TestDungeon.h"




//Just throw you're tests in here
int main() {

    TestRoom::TestTileGeneration4Doors();
    TestRoom::TestTileGeneration3DoorsEWS();
    TestRoom::TestTileGeneration3DoorsEWN();
    TestRoom::TestTileGeneration3DoorsENS();
    TestRoom::TestTileGeneration3DoorsSNW();
    TestDungeon::TestRoomIDs();
}