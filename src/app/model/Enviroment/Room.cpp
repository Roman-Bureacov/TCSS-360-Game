//
// Created by riley on 7/30/25.
//

#include "../../../include/Room.h"

//Monster function? I call that quality code.
void Room::generateRoom() {

    //(row, column) -> (i,j)
    for (int i = 0; i < roomSize; i++) {
        std::vector<DunText::DungeonTile> row;
        DunText::DungeonTile roomTile;

        for (int j = 0; j < roomSize; j++) {

            //Praying to god my schizophrenic mental conception, works.
            //I'm too goated to unit test. Toms face reading this comment : (
            roomTile = DunText::DungeonTile::Floor;

            if (i == 0 || i == roomSize - 1) roomTile
                = DunText::DungeonTile::HorizontalWall;
            if (j == 0 || j == roomSize - 1) roomTile
                =  DunText::DungeonTile::VerticalWall;

            if (i == 0) {
                if (j == 0) roomTile
                    = DunText::DungeonTile::NorthWestCorner;
                else if (j == roomSize - 1) roomTile
                    = DunText::DungeonTile::NorthEastCorner;
            } if (i == roomSize - 1) {
                if (j == 0) roomTile
                    = DunText::DungeonTile::SouthWestCorner;
                else if (j == roomSize - 1) roomTile
                    = DunText::DungeonTile::SouthEastCorner;
            }

            if (i == 0  && j == doorLocation && this->roomNorth) roomTile
                = DunText::DungeonTile::HorizontalDoor;
            if (i == roomSize - 1 && j == doorLocation && this->roomSouth) roomTile
                = DunText::DungeonTile::HorizontalDoor;
            if (j == 0  && i == doorLocation && this->roomWest) roomTile
                = DunText::DungeonTile::VerticalDoor;
            if (j == roomSize - 1 && i == doorLocation && this->roomEast) roomTile
                = DunText::DungeonTile::VerticalDoor;

            row.push_back(roomTile);
        }
        roomMap.push_back(row);
    }
}

std::vector<std::shared_ptr<AbstractCharacter>> Room::getCharacters() const {
}

void Room::setCharacters(std::vector<std::shared_ptr<AbstractCharacter>> characters) {

}

int Room::getRoomID() const {
    return roomID;
}

Room::Room() {
    this->generateRoom();
}

ConcreteRoomBuilder::ConcreteRoomBuilder() = default;

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

ConcreteRoomBuilder& ConcreteRoomBuilder::setEnemyAmount(int enAmount) {
    amount = enAmount;
    return *this;

}

std::shared_ptr<Room> ConcreteRoomBuilder::build() {

    auto room = std::make_shared<Room>();

    room->roomNorth = roomNorth;
    room->roomEast = roomEast;
    room->roomWest = roomWest;
    room->roomSouth = roomSouth;
    room->roomID = roomID;
    room->enemyAmount = amount;

    //Reset the builder
    bool roomNorth = true;
    bool roomEast = true;
    bool roomWest = true;
    bool roomSouth = true;

    int roomID = 0;
    int amount = 0;

    return room;

}
