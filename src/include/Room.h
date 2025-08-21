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
 * Represents a dungeon room the player can explore.
 * Handles room generation, serialization, and character placement.
 *
 * @author Riley Hopper
 * @version July 2025
 */
class Room final {
    friend class ConcreteRoomBuilder;

public:
    /**
     * Generates a new room that doesn't yet exist.
     * Creates a fresh tile map and serial representation.
     */
    void generateNonExistingRoom();

    /**
     * Loads an existing room from serialized data.
     * Reconstructs the tile map from stored string.
     */
    void generateExistingRoom();

    /**
     * Initializes the room.
     * Determines whether to generate new or load existing.
     */
    void initializeRoom();

    /**
     * Converts the room's tile map into a serializable string.
     */
    void serializeRoomMap();

    /** @return The unique ID of the room. */
    int getRoomID() const;

    /** @return True if there is a room to the north. */
    bool getNorth() const;

    /** @return True if there is a room to the east. */
    bool getEast() const;

    /** @return True if there is a room to the south. */
    bool getSouth() const;

    /** @return True if there is a room to the west. */
    bool getWest() const;

    /** @return Serialized string representation of the room's tile map. */
    std::string getSerialRoomMap() const;

    /** @return The fixed size of the room (roomSize x roomSize). */
    int getRoomSize() const;

    /** @return Vector of character IDs present in the room. */
    std::vector<long long> getCharacters() const;

    /** @return True if the room has already been generated. */
    bool getAlreadyGenerated() const;

    /** Sets the room's unique ID. */
    void setRoomID(int theRoomID);

    /** Sets whether there is a room to the north. */
    void setNorth(bool theNorth);

    /** Sets whether there is a room to the east. */
    void setEast(bool theEast);

    /** Sets whether there is a room to the south. */
    void setSouth(bool theSouth);

    /** Sets whether there is a room to the west. */
    void setWest(bool theWest);

    /** Marks the room as already generated. */
    void setAlreadyGenerated(bool theAlreadyMade);

    /** Sets the serialized tile map string. */
    void setSerialRoomMap(const std::string &theMap);

    /** Sets the ID of the first character. */
    void setChar1ID(long long theId);

    /** Sets the ID of the second character. */
    void setChar2ID(long long theId);

    /** Sets the ID of the third character. */
    void setChar3ID(long long theId);

    /**
     * Retrieves the dungeon tile map.
     * @return A 2D vector representing the room's layout.
     */
    std::vector<std::vector<DunText::DungeonTile>> getRoomTiles() const;

    /** Default destructor. */
    ~Room() = default;

    /** Constructs an empty room. */
    Room();

    /** Number of tiles per side in the room. */
    static constexpr int ROOMSIZE = 15;

    /** Center position used for door placement. */
    static constexpr int DOORLOCATION = (ROOMSIZE - 1) / 2;

    /** Pixel size of each tile for rendering. */
    static constexpr int TILESIZE = 100;

private:
    /** ID of the first character in the room. */
    long long myCharID1;

    /** ID of the second character in the room. */
    long long myCharID2;

    /** ID of the third character in the room. */
    long long mycharID3;

    /** 2D tile map representing the room layout. */
    std::vector<std::vector<DunText::DungeonTile>> roomMap;

    /** Serialized version of the tile map. */
    std::string mySerialRoomMap = "";

    /** Flag indicating if the room has already been generated. */
    bool myAlreadyGenerated = false;

    /** Flags for adjacent rooms. */
    bool myRoomNorth;
    bool myRoomEast;
    bool myRoomWest;
    bool myRoomSouth;

    /** Unique room identifier. */
    int myRoomID;

    /** Prints the room map to console (for testing). */
    void printRoomMap() const;

    /** Converts a string to a DungeonTile enum. */
    DunText::DungeonTile stringToDungeonTile(const std::string &theTile) const;

    /** Converts a DungeonTile enum to string. */
    std::string DungeonTileToString(const DunText::DungeonTile &theTile) const;
};

/**
 * Abstract builder interface for constructing Room objects.
 * Allows flexible configuration of room layout and character placement.
 */
class RoomBuilder {
public:
    virtual ~RoomBuilder() = default;

    virtual RoomBuilder& setRoomNorth(bool theNorth) = 0;
    virtual RoomBuilder& setRoomEast(bool theEast) = 0;
    virtual RoomBuilder& setRoomWest(bool theWest) = 0;
    virtual RoomBuilder& setRoomSouth(bool theSouth) = 0;
    virtual RoomBuilder& setRoomId(int theId) = 0;

    /** Sets the ID of the first character. */
    virtual RoomBuilder& setChar1ID(long long theID) = 0;

    /** Sets the ID of the second character. */
    virtual RoomBuilder& setChar2ID(long long theID) = 0;

    /** Sets the ID of the third character. */
    virtual RoomBuilder& setChar3ID(long long theID) = 0;

    /** Builds and returns the configured Room object. */
    virtual std::shared_ptr<Room> build() = 0;
};

/**
 * Concrete implementation of RoomBuilder.
 * Constructs Room objects with specified layout and character data.
 */
class ConcreteRoomBuilder final : public RoomBuilder {
public:
    /** Constructs a builder with default room flags. */
    ConcreteRoomBuilder();

    ConcreteRoomBuilder& setRoomNorth(bool theNorth) override;
    ConcreteRoomBuilder& setRoomEast(bool theEast) override;
    ConcreteRoomBuilder& setRoomWest(bool theWest) override;
    ConcreteRoomBuilder& setRoomSouth(bool theSouth) override;
    ConcreteRoomBuilder& setRoomId(int theId) override;

    ConcreteRoomBuilder& setChar1ID(long long theID) override;
    ConcreteRoomBuilder& setChar2ID(long long theID) override;
    ConcreteRoomBuilder& setChar3ID(long long theID) override;

    /** Builds and returns the configured Room object. */
    std::shared_ptr<Room> build() override;

private:
    /** Flags for adjacent rooms. */
    bool myRoomNorth = true;
    bool myRoomEast = true;
    bool myRoomWest = true;
    bool myRoomSouth = true;

    /** Character IDs for the room. */
    long long myCharID1;
    long long myCharID2;
    long long myCharID3;

    /** Unique room identifier. */
    int myRoomID = 0;
};

#endif // ROOM_H
