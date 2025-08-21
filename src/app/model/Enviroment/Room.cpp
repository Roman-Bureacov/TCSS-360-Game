//
// Created by riley on 7/30/25.
//

#include "../../../include/Room.h"




void Room::generateNonExistingRoom() {

    //Awful algorithm.
    //(row, column) -> (i,j)
    for (int i = 0; i < ROOMSIZE; i++) {
        for (int j = 0; j < ROOMSIZE; j++) {

            std::string roomTile = "F";

            if (i == 0 || i == ROOMSIZE - 1) roomTile
                                             = "HW";
            if (j == 0 || j == ROOMSIZE - 1) roomTile
                =  "VW";
            if (i == 0) {
                if (j == 0) roomTile
                    = "NWC";
                else if (j == ROOMSIZE - 1) roomTile
                    = "NEC";
            } if (i == ROOMSIZE - 1) {
                if (j == 0) roomTile
                    = "SWC";
                else if (j == ROOMSIZE - 1) roomTile
                    = "SEC";
            }
            if (i == 0  && j == DOORLOCATION && this->myRoomNorth) roomTile
                = "HD";
            if (i == ROOMSIZE - 1 && j == DOORLOCATION && this->myRoomSouth) roomTile
                = "HD";
            if (j == 0  && i == DOORLOCATION && this->myRoomWest) roomTile
                = "VD";
            if (j == ROOMSIZE - 1 && i == DOORLOCATION && this->myRoomEast) roomTile
                = "VD";

            mySerialRoomMap.append(roomTile);

            if (j == ROOMSIZE - 1) mySerialRoomMap.append(";");
            else mySerialRoomMap.append(",");
        }
    }
    this->myAlreadyGenerated = true;

}

std::vector<long long> Room::getCharacters() const {
    std::vector<long long> characters = std::vector<long long>();

    characters.push_back(this->myCharID1);
    characters.push_back(this->myCharID2);
    characters.push_back(this->mycharID3);

    return characters;
}

void Room::generateExistingRoom() {

    roomMap.clear();

    std::stringstream ss(mySerialRoomMap);
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

void Room::initializeRoom() {

    if (this->myAlreadyGenerated) {
        //load data from database here
        this->generateExistingRoom();
    } else {
        this->generateNonExistingRoom();
    }
}

void Room::serializeRoomMap() {

    if (roomMap.size() != ROOMSIZE) return;

    mySerialRoomMap.clear();
    //(row, column) -> (i,j)
    for (int i = 0; i < ROOMSIZE; i++) {
        for (int j = 0; j < ROOMSIZE; j++) {

            mySerialRoomMap.append(DungeonTileToString(roomMap[i][j]));


            if (j == ROOMSIZE - 1) mySerialRoomMap.append(";");
            else mySerialRoomMap.append(",");
        }
    }
}

void Room::setChar1ID(const long long theId) {
    myCharID1 = theId;
}

void Room::setChar2ID(const long long theId) {
    myCharID2 = theId;
}

bool Room::getAlreadyGenerated() const {
    return this->myAlreadyGenerated;
}

void Room::setChar3ID(const long long theId) {
    mycharID3 = theId;
}

int Room::getRoomID() const {
    return myRoomID;
}

bool Room::getNorth() const {
    return myRoomNorth;
}

bool Room::getEast() const {
    return myRoomEast;
}

bool Room::getSouth() const {
    return myRoomSouth;
}

bool Room::getWest() const {
    return myRoomWest;
}

std::string Room::getSerialRoomMap() const {
    return mySerialRoomMap;
}

int Room::getRoomSize() const {
    return ROOMSIZE;
}

void Room::setRoomID(const int theRoomID) {
    this->myRoomID = theRoomID;
}

void Room::setNorth(const bool theNorth) {
    this->myRoomNorth = theNorth;
}

void Room::setEast(const bool theEast) {
    this->myRoomEast = theEast;
}

void Room::setSouth(const bool theSouth) {
    this->myRoomSouth = theSouth;
}

void Room::setWest(const bool theWest) {
    this->myRoomWest = theWest;
}


void Room::setAlreadyGenerated(const bool theAlreadyMade) {
    this->myAlreadyGenerated = theAlreadyMade;
}

void Room::setSerialRoomMap(const std::string &theMap) {
    if (this == nullptr) {
        throw std::runtime_error("setSerialRoomMap called on null Room");
    }
    this->mySerialRoomMap = theMap;
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

DunText::DungeonTile Room::stringToDungeonTile(const std::string &theTile) const {
    if (theTile == "F") return DunText::DungeonTile::Floor;
    else if (theTile == "HW") return DunText::DungeonTile::HorizontalWall;
    else if (theTile == "VW") return DunText::DungeonTile::VerticalWall;
    else if (theTile == "NWC") return DunText::DungeonTile::NorthWestCorner;
    else if (theTile == "NEC") return DunText::DungeonTile::NorthEastCorner;
    else if (theTile == "SWC") return DunText::DungeonTile::SouthWestCorner;
    else if (theTile == "SEC") return DunText::DungeonTile::SouthEastCorner;
    else if (theTile == "HD") return DunText::DungeonTile::HorizontalDoor;
    else if (theTile == "VD") return DunText::DungeonTile::VerticalDoor;


    throw std::runtime_error("Unknown tile type: '" + theTile
        + "' in Room ID: " + std::to_string(myRoomID));


}

std::string Room::DungeonTileToString(const DunText::DungeonTile &theTile) const {

    switch (theTile) {
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


ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomNorth(const bool theNorth) {
    myRoomNorth = theNorth;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomEast(const bool theEast) {
    myRoomEast = theEast;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomWest(const bool theWest) {
    myRoomWest = theWest;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomSouth(const bool theSouth) {
    myRoomSouth = theSouth;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomId(const int theId) {
    myRoomID = theId;
    return *this;
}

ConcreteRoomBuilder & ConcreteRoomBuilder::setChar1ID(const long long theID) {
    myCharID1 = theID;
    return *this;
}

ConcreteRoomBuilder & ConcreteRoomBuilder::setChar2ID(const long long theID) {
    myCharID2 = theID;
    return *this;
}

ConcreteRoomBuilder & ConcreteRoomBuilder::setChar3ID(const long long theID) {
    myCharID3 = theID;
    return *this;
}

std::shared_ptr<Room> ConcreteRoomBuilder::build() {

    auto room = std::make_shared<Room>();

    room->setNorth(this->myRoomNorth);
    room->setEast(this->myRoomEast);
    room->setWest(this->myRoomWest);
    room->setSouth(this->myRoomSouth);
    room->setRoomID(this->myRoomID);
    room->setAlreadyGenerated(false);
    room->setChar1ID(this->myCharID1);
    room->setChar2ID(this->myCharID2);
    room->setChar3ID(this->myCharID3);

    room->initializeRoom();

    //Reset the builder
    this->myRoomNorth = true;
    this->myRoomEast = true;
    this->myRoomWest = true;
    this->myRoomSouth = true;
    this->myRoomID = 0;
    this->myCharID1 = 0;
    this->myCharID2 = 0;
    this->myCharID3 = 0;


    return room;


}


