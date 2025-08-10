//
// Created by riley on 7/30/25.
//

#include "../../../include/Room.h"


/**
 * Generates a string map of the dungeon if it doesn't already
 * exist.
 */
void Room::generateNonExistingRoom() {

    //Awful algorithm.
    //(row, column) -> (i,j)
    for (int i = 0; i < roomSize; i++) {
        for (int j = 0; j < roomSize; j++) {

            std::string roomTile = "F";

            if (i == 0 || i == roomSize - 1) roomTile
                                             = "HW";
            if (j == 0 || j == roomSize - 1) roomTile
                =  "VW";
            if (i == 0) {
                if (j == 0) roomTile
                    = "NWC";
                else if (j == roomSize - 1) roomTile
                    = "NEC";
            } if (i == roomSize - 1) {
                if (j == 0) roomTile
                    = "SWC";
                else if (j == roomSize - 1) roomTile
                    = "SEC";
            }
            if (i == 0  && j == doorLocation && this->roomNorth) roomTile
                = "HD";
            if (i == roomSize - 1 && j == doorLocation && this->roomSouth) roomTile
                = "HD";
            if (j == 0  && i == doorLocation && this->roomWest) roomTile
                = "VD";
            if (j == roomSize - 1 && i == doorLocation && this->roomEast) roomTile
                = "VD";

            serialRoomMap.append(roomTile);

            if (j == roomSize - 1) serialRoomMap.append(";");
            else serialRoomMap.append(",");
        }
    }
    this->alreadyGenerated = true;
    //this->generateCharacters();
}


/**
 * This takes a serialized, room map string and makes in the enum formate.
 */
void Room::generateExistingRoom() {

    roomMap.clear();

    std::stringstream ss(serialRoomMap);
    std::string rowStr;

    while (std::getline(ss, rowStr, ';')) {
        std::vector<DunText::DungeonTile> row;
        std::stringstream rowStream(rowStr);
        std::string tileStr;
        while (std::getline(rowStream, tileStr, ',')) {
            row.push_back(stringToDungeonTile(tileStr));
        }
        if (!row.empty()) roomMap.push_back(row);
    }



}

/**
 * This will either generate a new room if the room doesn't already exist or
 * generate an existing room.
 */
void Room::initializeRoom() {

    if (this->alreadyGenerated) {
        //load data from database here
        this->generateExsistingRoom();
    } else {
        this->generateNonExsistingRoom();
    }
}

/**
 * This takes a room map in enum form and puts into string form.
 */
void Room::serializeRoomMap() {

    serialRoomMap.clear();
    //(row, column) -> (i,j)
    for (int i = 0; i < roomSize; i++) {
        for (int j = 0; j < roomSize; j++) {

            serialRoomMap.append(DungeonTileToString(roomMap[i][j]));


            if (j == roomSize - 1) serialRoomMap.append(";");
            else serialRoomMap.append(",");
        }
    }

}




std::vector<std::shared_ptr<AbstractCharacter>> Room::getCharacters() const {
}


int Room::getRoomID() const {
    return roomID;
}

bool Room::getNorth() const {
    return roomNorth;
}

bool Room::getEast() const {
    return roomEast;
}

bool Room::getSouth() const {
    return roomSouth;
}

bool Room::getWest() const {
    return roomWest;
}

std::string Room::getSerialRoomMap() const {
    return serialRoomMap;
}

void Room::setRoomID(const int roomID) {
    this->roomID = roomID;
}

void Room::setNorth(const bool north) {
    this->roomNorth = north;
}

void Room::setEast(const bool east) {
    this->roomEast = east;
}

void Room::setSouth(const bool south) {
    this->roomSouth = south;
}

void Room::setWest(const bool west) {
    this->roomWest = west;
}


void Room::setAlreadyGenerated(const bool alreadyMade) {
    this->alreadyGenerated = alreadyMade;
}

void Room::setSerialRoomMap(const std::string &map) {
    this->serialRoomMap = map;
}

Room::Room() {}

void Room::printRoomMap() const {
    for (const auto& row : roomMap) {
        for (const auto& tile : row) {
            std::cout << DungeonTileToString(tile) << " ";
        }
        std::cout << "\n";
    }
}

/**
 * This takes a tile, string code and makes it an enum.
 * @param tile This is the string code for the tile
 * @return This is the corresponding enum to the tiles
 */
DunText::DungeonTile Room::stringToDungeonTile(const std::string &tile) const {
    if (tile == "F") return DunText::DungeonTile::Floor;
    else if (tile == "HW") return DunText::DungeonTile::HorizontalWall;
    else if (tile == "VW") return DunText::DungeonTile::VerticalWall;
    else if (tile == "NWC") return DunText::DungeonTile::NorthWestCorner;
    else if (tile == "NEC") return DunText::DungeonTile::NorthEastCorner;
    else if (tile == "SWC") return DunText::DungeonTile::SouthWestCorner;
    else if (tile == "SEC") return DunText::DungeonTile::SouthEastCorner;
    else if (tile == "HD") return DunText::DungeonTile::HorizontalDoor;
    else if (tile == "VD") return DunText::DungeonTile::VerticalDoor;


    throw std::runtime_error("Unknown tile type: '" + tile
        + "' in Room ID: " + std::to_string(roomID));


}

/**
 * This takes an enum tile and turns it into a string code.
 * @param tile an enum tile.
 * @return String code for tile.
 */
std::string Room::DungeonTileToString(const DunText::DungeonTile &tile) const {

    switch (tile) {
        case DunText::DungeonTile::HorizontalWall: return "HW";
        case DunText::DungeonTile::VerticalWall: return "VW";
        case DunText::DungeonTile::NorthWestCorner: return "NWC";
        case DunText::DungeonTile::NorthEastCorner: return "NEC";
        case DunText::DungeonTile::SouthWestCorner: return "SWC";
        case DunText::DungeonTile::SouthEastCorner: return "SEC";
        case DunText::DungeonTile::HorizontalDoor: return "HD";
        case DunText::DungeonTile::VerticalDoor: return "VD";
        default: return "F";
    }

}

ConcreteRoomBuilder::ConcreteRoomBuilder() = default;

/**
 * Sets if the room has been generated before.
 * @param alreadyMade boolean for if a room as been made.
 * @return Returns a concreteRoomBuilder reference.
 *
 */
ConcreteRoomBuilder& ConcreteRoomBuilder::setGenerated(const bool alreadyMade) {
    alreadyGenerated = alreadyMade;
    return *this;
}

/**
 * This sets if there is a room to north.
 * @param north Boolean for if there is a northern room.
 * @return Returns a concreteRoomBuilder reference.
 *
 */
ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomNorth(const bool north) {
    roomNorth = north;
    return *this;
}

/**
 * This sets if there is a room to east.
 * @param east Boolean for if there is an eastern room.
 * @return Returns a concreteRoomBuilder reference.
 *
 */
ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomEast(const bool east) {
    roomEast = east;
    return *this;
}

/**
 * This sets if there is a room to west.
 * @param west Boolean for if there is a western room.
 * @return Returns a concreteRoomBuilder reference.

 */
ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomWest(const bool west) {
    roomWest = west;
    return *this;
}

/**
 * This sets if there is a room to south.
 * @param south Boolean for if there is a southern room.
 * @return Returns a concreteRoomBuilder reference.
 */
ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomSouth(const bool south) {
    roomSouth = south;
    return *this;
}

/**
 * This sets the id for the room.
 * @param id rooms id.
 * @return Returns a concreteRoomBuilder reference.
 */
ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomId(const int id) {
    roomID = id;
    return *this;
}

/**
 * This builds the rooms according to the build rules.
 * @return A shared smart pointer to the built room.
 */
std::shared_ptr<Room> ConcreteRoomBuilder::build() {

    auto room = std::make_shared<Room>();

    room->setNorth(roomNorth);
    room->setEast(roomEast);
    room->setWest(roomWest);
    room->setSouth(roomSouth);
    room->setRoomID(roomID);
    room->setAlreadyGenerated(alreadyGenerated);

    room->initializeRoom();

    //Reset the builder
    this->roomNorth = true;
    this->roomEast = true;
    this->roomWest = true;
    this->roomSouth = true;
    this->roomID = 0;
    this->alreadyGenerated = false;

    return room;

}