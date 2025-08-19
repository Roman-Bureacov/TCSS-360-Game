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
    void setRoomID(int roomID);

    /** Sets whether there is a room to the north. */
    void setNorth(bool north);

    /** Sets whether there is a room to the east. */
    void setEast(bool east);

    /** Sets whether there is a room to the south. */
    void setSouth(bool south);

    /** Sets whether there is a room to the west. */
    void setWest(bool west);

    /** Marks the room as already generated. */
    void setAlreadyGenerated(bool alreadyMade);

    /** Sets the serialized tile map string. */
    void setSerialRoomMap(const std::string &map);

    /** Sets the ID of the first character. */
    void setChar1ID(long long ID);

    /** Sets the ID of the second character. */
    void setChar2ID(long long ID);

    /** Sets the ID of the third character. */
    void setChar3ID(long long ID);

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
    static constexpr int roomSize = 15;

    /** Center position used for door placement. */
    static constexpr int doorLocation = (roomSize - 1) / 2;

    /** Pixel size of each tile for rendering. */
    static constexpr int tileSize = 100;

private:
    /** ID of the first character in the room. */
    long long charID1;

    /** ID of the second character in the room. */
    long long charID2;

    /** ID of the third character in the room. */
    long long charID3;

    /** 2D tile map representing the room layout. */
    std::vector<std::vector<DunText::DungeonTile>> roomMap;

    /** Serialized version of the tile map. */
    std::string serialRoomMap = "";

    /** Flag indicating if the room has already been generated. */
    bool alreadyGenerated = false;

    /** Flags for adjacent rooms. */
    bool roomNorth;
    bool roomEast;
    bool roomWest;
    bool roomSouth;

    /** Unique room identifier. */
    int roomID;

    /** Prints the room map to console (for testing). */
    void printRoomMap() const;

    /** Converts a string to a DungeonTile enum. */
    DunText::DungeonTile stringToDungeonTile(const std::string &tile) const;

    /** Converts a DungeonTile enum to string. */
    std::string DungeonTileToString(const DunText::DungeonTile &tile) const;
};

/**
 * Abstract builder interface for constructing Room objects.
 * Allows flexible configuration of room layout and character placement.
 */
class RoomBuilder {
public:
    virtual ~RoomBuilder() = default;

    virtual RoomBuilder& setRoomNorth(bool north) = 0;
    virtual RoomBuilder& setRoomEast(bool east) = 0;
    virtual RoomBuilder& setRoomWest(bool west) = 0;
    virtual RoomBuilder& setRoomSouth(bool south) = 0;
    virtual RoomBuilder& setRoomId(int id) = 0;

    /** Sets the ID of the first character. */
    virtual RoomBuilder& setChar1ID(long long ID) = 0;

    /** Sets the ID of the second character. */
    virtual RoomBuilder& setChar2ID(long long ID) = 0;

    /** Sets the ID of the third character. */
    virtual RoomBuilder& setChar3ID(long long ID) = 0;

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

    ConcreteRoomBuilder& setRoomNorth(bool north) override;
    ConcreteRoomBuilder& setRoomEast(bool east) override;
    ConcreteRoomBuilder& setRoomWest(bool west) override;
    ConcreteRoomBuilder& setRoomSouth(bool south) override;
    ConcreteRoomBuilder& setRoomId(int id) override;

    ConcreteRoomBuilder& setChar1ID(long long ID) override;
    ConcreteRoomBuilder& setChar2ID(long long ID) override;
    ConcreteRoomBuilder& setChar3ID(long long ID) override;

    /** Builds and returns the configured Room object. */
    std::shared_ptr<Room> build() override;

private:
    /** Flags for adjacent rooms. */
    bool roomNorth = true;
    bool roomEast = true;
    bool roomWest = true;
    bool roomSouth = true;

    /** Character IDs for the room. */
    long long charID1;
    long long charID2;
    long long charID3;

    /** Unique room identifier. */
    int roomID = 0;
};

#endif // ROOM_H
