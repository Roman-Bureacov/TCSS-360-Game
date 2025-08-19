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

#include "DungeonTextures.h"



/**
 * This is the room class, it creates the rooms the player will be within.
 *
 * @author Riley Hopper
 * @version July 2025
 */
class Room final {
    friend class ConcreteRoomBuilder;
public:
    /**
     * This generates a room that doesn't already exist
     * It generates the serial map of the dungeon, this should
     * Be used when the room is first being generated.
     */
    void generateNonExistingRoom();

    /**
     * This generates a room from the database, it
     * Takes the inputted serial map and then set up
     * the dungeon tile map.
     */
    void generateExistingRoom();


    /**
     * This initializes a room this will
     * either create a new room or an existing one.
     */
    void initializeRoom();

    /**
     * Turns the tiles into a serializable
     * string.
     */
    void serializeRoomMap();

    /**
     *
     * @return rooms ID
     */
    int getRoomID() const;

    /**
     *
     * @return A bool of it there is a room to the north.
     */
    bool getNorth() const;

    /**
     *
     * @return A bool of it there is a room to the east.
     */
    bool getEast() const;

    /**
     *
     * @return A bool of it there is a room to the south.
     */
    bool getSouth() const;

    /**
     *
     * @return A bool of it there is a room to the west.
     */
    bool getWest() const;

    /**
     *
     * @return a string of the room tile.
     */
    std::string getSerialRoomMap() const;

    /**
     *
     * @return The size of the room.
     */
    int getRoomSize() const;

    /**
     * Returns the ids of the characters in the room.
     * @return A vector of character ids
     */
    std::vector<long long> getCharacters() const;

    /**
     *
     * @return This returns if the room has already been generated.
     */
    bool getAlreadyGenerated() const;

    /**
     * Sets the rooms ID.
     * @param roomID ID of this room
     */
    void setRoomID(int roomID);

    /**
     * Sets a room to the north.
     * @param north bool for if there is a room to the north.
     */
    void setNorth(bool north);
    /**
     * Sets a room to the east.
     * @param east bool for if there is a room to the east.
     */
    void setEast(bool east);
    /**
     * Sets a room to the south.
     * @param south bool for if there is a room to the south.
     */
    void setSouth(bool south);
    /**
     * Sets a room to the west.
     * @param west bool for if there is a room to the west.
     */
    void setWest(bool west);

    /**
     * Sets the room to have already been made.
     * @param alreadyMade a bool if the room has already been made.
     */
    void setAlreadyGenerated(bool alreadyMade);

    /**
     * Sets the serial string of the rooms map.
     * @param map a serialized string of the rooms map.
     */
    void setSerialRoomMap(const std::string &map);

    /**
     *  Sets the id of character 1.
     * @param ID id of the character
     */
    void setChar1ID(long long ID);

    /**
     *  Sets the id of character 2.
     * @param ID id of the character
     */
    void setChar2ID(long long ID);

    /**
     *  Sets the id of character 3.
     * @param ID id of the character
     */
    void setChar3ID(long long ID);

    /**
     * This returns the dungeons tile map to the caller.
     * @return This is a 2D vector representing the dungeon.
     */
    std::vector<std::vector<DunText::DungeonTile>> getRoomTiles() const;

    //It should always be a smart pointer
    ~Room() = default;
    Room();
    /**This is the amount of tiles in the room roomSize X roomSize*/
    static constexpr int roomSize = 15;
    /**Position of the room tile*/
    static constexpr int doorLocation = (roomSize - 1) / 2;
    /**This is the actually size of each tile in rendering*/
    static constexpr int tileSize = 100;//TODO change if needed.


private:
    /**This is the id of the first enemy.*/
    long long charID1;
    /**This is the id of the second enemy.*/
    long long charID2;
    /**This is hte id of the third enemy.*/
    long long charID3;


    /**This is the map as an enum tile map.*/
    std::vector<std::vector<DunText::DungeonTile>> roomMap;

    /**This is the serialized map of the room.*/
    std::string serialRoomMap = "";

    /**This sets if a room has already been generated.*/
    bool alreadyGenerated = false;

    /**North room flag.*/
    bool roomNorth;
    /**east room flag.*/
    bool roomEast;
    /**West room flag.*/
    bool roomWest;
    /**South room flag.*/
    bool roomSouth;
    int roomID;




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
    /**
    *  Sets the id of character 1.
    * @param ID id of the character
    */
    virtual RoomBuilder& setChar1ID(long long ID) = 0;

    /**
     *  Sets the id of character 2.
     * @param ID id of the character
     */
    virtual RoomBuilder& setChar2ID(long long ID) = 0;

    /**
     *  Sets the id of character 3.
     * @param ID id of the character
     */
    virtual RoomBuilder& setChar3ID(long long ID) = 0;

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
    /**
   *  Sets the id of character 1.
   * @param ID id of the character
   */
    ConcreteRoomBuilder&  setChar1ID(long long ID) override;

    /**
     *  Sets the id of character 2.
     * @param ID id of the character
     */
    ConcreteRoomBuilder&  setChar2ID(long long ID) override;

    /**
     *  Sets the id of character 3.
     * @param ID id of the character
     */
    ConcreteRoomBuilder& setChar3ID(long long ID) override;

    std::shared_ptr<Room> build() override;

private:
    bool roomNorth = true;
    bool roomEast = true;
    bool roomWest = true;
    bool roomSouth = true;
    /**This is the id of the first enemy.*/
    long long charID1;
    /**This is the id of the second enemy.*/
    long long charID2;
    /**This is hte id of the third enemy.*/
    long long charID3;

    int roomID = 0;
};





#endif //ROOM_H
