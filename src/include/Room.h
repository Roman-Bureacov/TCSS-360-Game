//
// Created by riley on 7/30/25.
//

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "AbstractCharacter.h"



class Room {

public:
    int getRoomID();

    std::vector<std::vector<std::string>> generateRoom();
    std::vector<AbstractCharacter> getCharacters();
    void setCharacters(std::vector<AbstractCharacter> characters);




private:

    std::vector<std::vector<std::string>> roomMap;
    std::vector<AbstractCharacter> characters;

    const int roomID; //Might not want it to be constant.





};



#endif //ROOM_H
