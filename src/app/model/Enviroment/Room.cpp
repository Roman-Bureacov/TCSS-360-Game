//
// Created by riley on 7/30/25.
//

#include "../../../include/Room.h"



void Room::generateNonExsistingRoom() {

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
    this->generateCharacters();
}

void Room::generateCharacters() {

    //TODO


}

void Room::generateExsistingRoom() {

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

void Room::initializeRoom() {

    if (this->alreadyGenerated) {
        //load data from database here
        this->generateExsistingRoom();
    } else {
        this->generateNonExsistingRoom();
    }
}

void Room::serializeRoomMap() {

    serialRoomMap.clear();
    //Awful algorithm.
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

void Room::setCharacters(std::vector<int> ids) {

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

void Room::setEnemyAmount(const int amount) {
    this->enemyAmount = amount;
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

ConcreteRoomBuilder& ConcreteRoomBuilder::setGenerated(const bool alreadyMade) {
    alreadyGenerated = alreadyMade;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomNorth(const bool north) {
    roomNorth = north;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomEast(const bool east) {
    roomEast = east;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomWest(const bool west) {
    roomWest = west;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomSouth(const bool south) {
    roomSouth = south;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setRoomId(const int id) {
    roomID = id;
    return *this;
}

ConcreteRoomBuilder& ConcreteRoomBuilder::setEnemyAmount(const int enAmount) {
    amount = enAmount;
    return *this;

}

std::shared_ptr<Room> ConcreteRoomBuilder::build() {

    auto room = std::make_shared<Room>();

    room->setNorth(roomNorth);
    room->setEast(roomEast);
    room->setWest(roomWest);
    room->setSouth(roomSouth);
    room->setRoomID(roomID);
    room->setEnemyAmount(amount);
    room->setAlreadyGenerated(alreadyGenerated);

    room->initializeRoom();

    //Reset the builder
    this->roomNorth = true;
    this->roomEast = true;
    this->roomWest = true;
    this->roomSouth = true;
    this->roomID = 0;
    this->amount = 0;
    this->alreadyGenerated = false;  // maybe reset this too?

    return room;

}


