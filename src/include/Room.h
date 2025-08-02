//
// Created by riley on 7/30/25.
//

#ifndef ROOM_H
#define ROOM_H

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


#include "AbstractCharacter.h"
#include "DungeonTextures.h"



class Room final {

public:
    void generateNonExsistingRoom();
    void generateCharacters();
    void generateExsistingRoom();
    void initializeRoom();

    //This is for storing, and retriving textures.
    void serializeRoomMap();

    std::vector<std::shared_ptr<AbstractCharacter>> getCharacters() const;

    void setCharacters(std::vector<int> ids);

    int getRoomID() const;
    bool getNorth() const;
    bool getEast() const;
    bool getSouth() const;
    bool getWest() const;

    void setRoomID(int roomID);
    void setNorth(bool north);
    void setEast(bool east);
    void setSouth(bool south);
    void setWest(bool west);
    void setEnemyAmount(int amount);
    void setAlreadyGenerated(bool alreadyMade);
    void setSerialRoomMap(const std::string &map);

    Room();
    ~Room() = default;
private:

    //active memory.
    std::vector<std::shared_ptr<AbstractCharacter>> characters;
    std::vector<std::vector<DunText::DungeonTile>> roomMap;

    //Non-active memory.
    std::vector<int> characterIDs;
    std::string serialRoomMap;

    //this determines how the room is made.
    bool alreadyGenerated = false;

    //Door flags
    bool roomNorth;
    bool roomEast;
    bool roomWest;
    bool roomSouth;
    int enemyAmount;
    int roomID;

    //2 blocks for the border, and 13 for the interior.
    //The reason it's an odd number is for the door to be centered.
    const int roomSize = 15;
    const int doorLocation = (roomSize - 1) / 2;

    //For testing
    void printRoomMap() const;

    //Helper function
    DunText::DungeonTile stringToDungeonTile(const std::string &tile) const;
    std::string DungeonTileToString(const DunText::DungeonTile &tile) const;

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
    virtual RoomBuilder& setGenerated(bool alreadyMade) = 0;

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
    ConcreteRoomBuilder& setGenerated(bool alreadyMade) override;
    std::shared_ptr<Room> build() override;

private:
    bool roomNorth = true;
    bool roomEast = true;
    bool roomWest = true;
    bool roomSouth = true;
    bool alreadyGenerated = false;

    int roomID = 0;
    int amount = 0;

};





#endif //ROOM_H
