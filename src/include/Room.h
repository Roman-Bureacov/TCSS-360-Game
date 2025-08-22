//
// Created by Riley on 7/30/25.
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

    /**
     * Retrieves the unique ID of the room.
     *
     * @return The room's unique identifier.
     */
    int getRoomID() const;

    /**
     * Checks if there is a room to the north.
     *
     * @return True if a northern room exists.
     */
    bool getNorth() const;

    /**
     * Checks if there is a room to the east.
     *
     * @return True if an eastern room exists.
     */
    bool getEast() const;

    /**
     * Checks if there is a room to the south.
     *
     * @return True if a southern room exists.
     */
    bool getSouth() const;

    /**
     * Checks if there is a room to the west.
     *
     * @return True if a western room exists.
     */
    bool getWest() const;

    /**
     * Retrieves the serialized string representation of the room's tile map.
     *
     * @return Serialized tile map string.
     */
    std::string getSerialRoomMap() const;

    /**
     * Retrieves the fixed size of the room.
     *
     * @return Room size in tiles (ROOMSIZE x ROOMSIZE).
     */
    int getRoomSize() const;

    /**
     * Retrieves the IDs of characters present in the room.
     *
     * @return Vector of character IDs.
     */
    std::vector<long long> getCharacters() const;

    /**
     * Checks if the room has already been generated.
     *
     * @return True if generation has occurred.
     */
    bool getAlreadyGenerated() const;

    /**
     * Sets the room's unique ID.
     *
     * @param theRoomID The ID to assign.
     */
    void setRoomID(int theRoomID);

    /**
     * Sets the presence of a northern room.
     *
     * @param theNorth True if a room exists to the north.
     */
    void setNorth(bool theNorth);

    /**
     * Sets the presence of an eastern room.
     *
     * @param theEast True if a room exists to the east.
     */
    void setEast(bool theEast);

    /**
     * Sets the presence of a southern room.
     *
     * @param theSouth True if a room exists to the south.
     */
    void setSouth(bool theSouth);

    /**
     * Sets the presence of a western room.
     *
     * @param theWest True if a room exists to the west.
     */
    void setWest(bool theWest);

    /**
     * Marks the room as already generated.
     *
     * @param theAlreadyMade True if generation has occurred.
     */
    void setAlreadyGenerated(bool theAlreadyMade);

    /**
     * Sets the serialized tile map string.
     *
     * @param theMap The serialized map string.
     */
    void setSerialRoomMap(const std::string &theMap);

    /**
     * Sets the ID of the first character.
     *
     * @param theId Character ID.
     */
    void setChar1ID(long long theId);

    /**
     * Sets the ID of the second character.
     *
     * @param theId Character ID.
     */
    void setChar2ID(long long theId);

    /**
     * Sets the ID of the third character.
     *
     * @param theId Character ID.
     */
    void setChar3ID(long long theId);

    /**
     * Retrieves the dungeon tile map.
     *
     * @return A 2D vector representing the room's layout.
     */
    std::vector<std::vector<DunText::DungeonTile>> getRoomTiles() const;

    /**
     * Default destructor.
     */
    ~Room() = default;

    /**
     * Constructs an empty room.
     */
    Room();

    /**Number of tiles per side in the room.*/
    static constexpr int ROOMSIZE = 15;

    /**Center position used for door placement.*/
    static constexpr int DOORLOCATION = (ROOMSIZE - 1) / 2;

    /**Pixel size of each tile for rendering.*/
    static constexpr int TILESIZE = 100;

private:
    /**ID of the first character in the room.*/
    long long myCharID1;

    /**ID of the second character in the room.*/
    long long myCharID2;

    /**ID of the third character in the room.*/
    long long mycharID3;

    /**2D tile map representing the room layout.*/
    std::vector<std::vector<DunText::DungeonTile>> roomMap;

    /**Serialized version of the tile map.*/
    std::string mySerialRoomMap = "";

    /**Flag indicating if the room has already been generated.*/
    bool myAlreadyGenerated = false;

    /**Flag indicating presence of a northern room.*/
    bool myRoomNorth;

    /**Flag indicating presence of an eastern room.*/
    bool myRoomEast;

    /**Flag indicating presence of a western room.*/
    bool myRoomWest;

    /**Flag indicating presence of a southern room.*/
    bool myRoomSouth;

    /**Unique room identifier.*/
    int myRoomID;

    /**Prints the room map to console (for testing).
    */
    void printRoomMap() const;

    /**
     * Converts a string to a DungeonTile enum.
     *
     * @param theTile The string to convert.
     * @return Corresponding DungeonTile enum.
     */
    DunText::DungeonTile stringToDungeonTile(const std::string &theTile) const;

    /**
     * Converts a DungeonTile enum to string.
     *
     * @param theTile The tile to convert.
     * @return Corresponding string representation.
     */
    std::string DungeonTileToString(const DunText::DungeonTile &theTile) const;
};

/**
 * Abstract builder interface for constructing Room objects.
 * Allows flexible configuration of room layout and character placement.
 */
class RoomBuilder {
public:
    /**
     * Virtual destructor for safe polymorphic cleanup.
     */
    virtual ~RoomBuilder() = default;

    /**
     * Sets whether the room has a northern neighbor.
     *
     * @param theNorth True if a room exists to the north.
     * @return Reference to this builder for chaining.
     */
    virtual RoomBuilder& setRoomNorth(bool theNorth) = 0;

    /**
     * Sets whether the room has an eastern neighbor.
     *
     * @param theEast True if a room exists to the east.
     * @return Reference to this builder for chaining.
     */
    virtual RoomBuilder& setRoomEast(bool theEast) = 0;

    /**
     * Sets whether the room has a western neighbor.
     *
     * @param theWest True if a room exists to the west.
     * @return Reference to this builder for chaining.
     */
    virtual RoomBuilder& setRoomWest(bool theWest) = 0;

    /**
     * Sets whether the room has a southern neighbor.
     *
     * @param theSouth True if a room exists to the south.
     * @return Reference to this builder for chaining.
     */
    virtual RoomBuilder& setRoomSouth(bool theSouth) = 0;

    /**
     * Sets the unique identifier for the room.
     *
     * @param theId The room ID to assign.
     * @return Reference to this builder for chaining.
     */
    virtual RoomBuilder& setRoomId(int theId) = 0;

    /**
     * Sets the ID of the first character to be placed in the room.
     *
     * @param theID Unique character ID.
     * @return Reference to this builder for chaining.
     */
    virtual RoomBuilder& setChar1ID(long long theID) = 0;

    /**
     * Sets the ID of the second character to be placed in the room.
     *
     * @param theID Unique character ID.
     * @return Reference to this builder for chaining.
     */
    virtual RoomBuilder& setChar2ID(long long theID) = 0;

    /**
     * Sets the ID of the third character to be placed in the room.
     *
     * @param theID Unique character ID.
     * @return Reference to this builder for chaining.
     */
    virtual RoomBuilder& setChar3ID(long long theID) = 0;

    /**
     * Builds and returns the configured Room object.
     * Applies all previously set parameters.
     *
     * @return Shared pointer to the constructed Room.
     */
    virtual std::shared_ptr<Room> build() = 0;
};


/**
 * Concrete implementation of RoomBuilder.
 * Constructs Room objects with specified layout and character data.
 */
class ConcreteRoomBuilder final : public RoomBuilder {
public:
    /**
     * Constructs a builder with default room flags and uninitialized character IDs.
     */
    ConcreteRoomBuilder();

    /**
     * Sets whether the room has a northern neighbor.
     *
     * @param theNorth True if a room exists to the north.
     * @return Reference to this builder for chaining.
     */
    ConcreteRoomBuilder& setRoomNorth(bool theNorth) override;

    /**
     * Sets whether the room has an eastern neighbor.
     *
     * @param theEast True if a room exists to the east.
     * @return Reference to this builder for chaining.
     */
    ConcreteRoomBuilder& setRoomEast(bool theEast) override;

    /**
     * Sets whether the room has a western neighbor.
     *
     * @param theWest True if a room exists to the west.
     * @return Reference to this builder for chaining.
     */
    ConcreteRoomBuilder& setRoomWest(bool theWest) override;

    /**
     * Sets whether the room has a southern neighbor.
     *
     * @param theSouth True if a room exists to the south.
     * @return Reference to this builder for chaining.
     */
    ConcreteRoomBuilder& setRoomSouth(bool theSouth) override;

    /**
     * Sets the unique identifier for the room.
     *
     * @param theId The room ID to assign.
     * @return Reference to this builder for chaining.
     */
    ConcreteRoomBuilder& setRoomId(int theId) override;

    /**
     * Sets the ID of the first character to be placed in the room.
     *
     * @param theID Unique character ID.
     * @return Reference to this builder for chaining.
     */
    ConcreteRoomBuilder& setChar1ID(long long theID) override;

    /**
     * Sets the ID of the second character to be placed in the room.
     *
     * @param theID Unique character ID.
     * @return Reference to this builder for chaining.
     */
    ConcreteRoomBuilder& setChar2ID(long long theID) override;

    /**
     * Sets the ID of the third character to be placed in the room.
     *
     * @param theID Unique character ID.
     * @return Reference to this builder for chaining.
     */
    ConcreteRoomBuilder& setChar3ID(long long theID) override;

    /**
     * Builds and returns the configured Room object.
     * Applies all previously set parameters.
     *
     * @return Shared pointer to the constructed Room.
     */
    std::shared_ptr<Room> build() override;

private:
    /**Indicates whether the room has a northern neighbor. Default is true.*/
    bool myRoomNorth = true;

    /**Indicates whether the room has an eastern neighbor.Default is true.*/
    bool myRoomEast = true;

    /**Indicates whether the room has a western neighbor. Default is true.*/
    bool myRoomWest = true;

    /**Indicates whether the room has a southern neighbor.Default is true.*/
    bool myRoomSouth = true;

    /**ID of the first character to be placed in the room.Must be set before building.*/
    long long myCharID1;

    /**ID of the second character to be placed in the room.Must be set before building.*/
    long long myCharID2;

    /**ID of the third character to be placed in the room.Must be set before building.*/
    long long myCharID3;

    /**Unique identifier for the room being built. Default is 0.*/
    int myRoomID = 0;
};

#endif // ROOM_H
