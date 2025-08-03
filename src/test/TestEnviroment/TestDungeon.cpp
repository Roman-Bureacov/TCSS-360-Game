//
// Created by riley on 8/3/25.
//

#include "../../include/TestDungeon.h"

#include "Dungeon.h"


bool TestDungeon::TestRoomIDs() {


    Dungeon *dungeon = Dungeon::DungeonInstance();

    std::vector<std::vector<int>> idMap = {
        {100, 101, 102, 103, 104, 105, 106, 107, 108, 109},
        {110, 111, 112, 113, 114, 115, 116, 117, 118, 119},
        {120, 121, 122, 123, 124, 125, 126, 127, 128, 129},
        {130, 131, 132, 133, 134, 135, 136, 137, 138, 139},
        {140, 141, 142, 143, 144, 145, 146, 147, 148, 149},
        {150, 151, 152, 153, 154, 155, 156, 157, 158, 159},
        {160, 161, 162, 163, 164, 165, 166, 167, 168, 169},
        {170, 171, 172, 173, 174, 175, 176, 177, 178, 179},
        {180, 181, 182, 183, 184, 185, 186, 187, 188, 189},
        {190, 191, 192, 193, 194, 195, 196, 197, 198, 199}
    };


    dungeon->generateDungeon();
    auto actual = dungeon->getMap();



    //(row, column) -> (i,j)
    for (int i = 0; i < idMap.size(); i++) {
        for (int j = 0; j < idMap[i].size(); j++) {
            if (idMap[i][j] != actual[i][j] ) {
                std::cout << "TestCase: TestRoomIDs failed, at "<< idMap[i][j] << ";" << std::endl;
                return false;
            }
        }
    }
    std::cout << "TestCase: TestRoomIDs passed;" << std::endl;
    return false;





}
