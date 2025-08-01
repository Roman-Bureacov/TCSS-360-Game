//
// Created by riley on 7/30/25.
//

#include "../../../include/Room.h"

std::vector<std::vector<std::string>> Room::generateRoom() {
}

std::vector<std::shared_ptr<AbstractCharacter>> Room::getCharacters() const {
}

void Room::setCharacters(std::vector<std::shared_ptr<AbstractCharacter>> characters) {

}

int Room::getRoomID() const {
    return roomID;
}

Room::Room() {


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
