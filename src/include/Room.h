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
    std::vector<std::vector<std::string>> generateRoom();

    std::vector<std::shared_ptr<AbstractCharacter>> getCharacters() const;

    void setCharacters(std::vector<std::shared_ptr<AbstractCharacter>> characters);

    int getRoomID() const;

    Room(int roomID);
    ~Room() = default;

    //Door flags
    bool roomNorth;
    bool roomEast;
    bool roomWest;
    bool roomSouth;

    int enemyAmount;




private:

    std::vector<std::vector<std::string>> roomMap;

    std::vector<std::shared_ptr<AbstractCharacter>> characters;

    int roomID;


};

class RoomBuilder {

public:
    virtual void setRoomNorth(bool north) = 0;
    virtual void setRoomEast(bool east) = 0;
    virtual void setRoomWest(bool west) = 0;
    virtual void setRoomSouth(bool south) = 0;

    virtual std::shared_ptr<Room> build() = 0;

};

class ConcreteRoomBuilder : public RoomBuilder {
public:
    ConcreteRoomBuilder();
    void setRoomNorth(bool north) override;
    void setRoomEast(bool east) override;
    void setRoomWest(bool west) override;
    void setRoomSouth(bool south) override;
    std::shared_ptr<Room> build() override;

private:
    bool roomNorth = false;
    bool roomEast = false;
    bool roomWest = false;
    bool roomSouth = false;

    int roomID;


};




#endif //ROOM_H
