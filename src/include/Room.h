//
// Created by riley on 7/30/25.
//

#ifndef ROOM_H
#define ROOM_H

#include <memory>
#include <string>
#include <vector>

#include "AbstractCharacter.h"
#include "DungeonTextures.h"



class Room final {

public:
    generateRoom();

    std::vector<std::shared_ptr<AbstractCharacter>> getCharacters() const;

    void setCharacters(std::vector<std::shared_ptr<AbstractCharacter>> characters);

    int getRoomID() const;
    bool getNorth() const;
    bool getEast() const;
    bool getSouth() const;
    bool getWest() const;

    void setRoomID(int roomID);

    //Door flags
    //Gotta ask tom how to not break encapsulation with builder
    bool roomNorth;
    bool roomEast;
    bool roomWest;
    bool roomSouth;

    int enemyAmount;

    int roomID;

    Room();
    ~Room() = default;
private:

    std::vector<std::vector<DunText::DungeonTile>> roomMap;
    std::vector<std::shared_ptr<AbstractCharacter>> characters;
    //2 blocks for the border, and 13 for the interior.
    //The reason it's an odd number is for the door to be centered.
    const int roomSize = 15;
    const int doorLocation = (roomSize - 1) / 2;





};

class RoomBuilder {

public:
    virtual ~RoomBuilder() = default;

    virtual RoomBuilder& setRoomNorth(bool north) = 0;
    virtual RoomBuilder& setRoomEast(bool east) = 0;
    virtual RoomBuilder& setRoomWest(bool west) = 0;
    virtual RoomBuilder& setRoomSouth(bool south) = 0;
    virtual RoomBuilder& setRoomId(int id) = 0;
    virtual RoomBuilder& setEnemyAmount(int amount) = 0;

    virtual std::shared_ptr<Room> build() = 0;

};

class ConcreteRoomBuilder final : public RoomBuilder {
public:
    ConcreteRoomBuilder();
    ConcreteRoomBuilder& setRoomNorth(bool north) override;
    ConcreteRoomBuilder& setRoomEast(bool east) override;
    ConcreteRoomBuilder& setRoomWest(bool west) override;
    ConcreteRoomBuilder& setRoomSouth(bool south) override;
    ConcreteRoomBuilder& setRoomId(int id) override;
    ConcreteRoomBuilder& setEnemyAmount(int enAmount) override;
    std::shared_ptr<Room> build() override;

private:
    bool roomNorth = true;
    bool roomEast = true;
    bool roomWest = true;
    bool roomSouth = true;

    int roomID = 0;
    int amount = 0;


};




#endif //ROOM_H
