//
// Created by riley on 7/30/25.
//

#ifndef ROOM_H
#define ROOM_H

#include <memory>
#include <string>
#include <vector>

#include "AbstractCharacter.h"



class Room {

public:
    int getRoomID();

    std::vector<std::vector<std::string>> generateRoom();
    std::vector<AbstractCharacter> getCharacters();

    void setCharacters(std::vector<AbstractCharacter> characters);

    Room(const int roomID);
    ~Room();

    //When a room is being generated it will check these to see if it needs doors in that direction.
    bool roomNorth;
    bool roomEast;
    bool roomWest;
    bool roomSouth;

    int enemyAmount;




private:

    std::vector<std::vector<std::string>> roomMap;
    std::vector<AbstractCharacter> characters;

    const int roomID; //Might not want it to be constant.


};

class RoomBuilder {

public:
    virtual void setRoomNorth(const bool roomNorth);
    virtual void setRoomEast(const bool roomEast);
    virtual void setRoomWest(const bool roomWest);
    virtual void setRoomSouth(const bool roomSouth);

    virtual std::shared_ptr<Room> build();

};
class ConcreteRoomBuilder : public RoomBuilder {
public:
    ConcreteRoomBuilder();
    void setRoomNorth(const bool roomNorth) override;
    void setRoomEast(const bool roomEast) override;
    void setRoomWest(const bool roomWest) override;
    void setRoomSouth(const bool roomSouth) override;
    std::shared_ptr<Room> build() override;


};




#endif //ROOM_H
