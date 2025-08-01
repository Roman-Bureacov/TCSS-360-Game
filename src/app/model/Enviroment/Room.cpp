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
}

Room::Room(int roomID) : roomID(roomID) {


}

ConcreteRoomBuilder::ConcreteRoomBuilder() {
}

void ConcreteRoomBuilder::setRoomNorth(bool north) {
    roomNorth = north;
}

void ConcreteRoomBuilder::setRoomEast(bool east) {
    roomEast = east;
}

void ConcreteRoomBuilder::setRoomWest(bool west) {
    roomWest = west;
}

void ConcreteRoomBuilder::setRoomSouth(bool south) {
    roomSouth = south;
}

std::shared_ptr<Room> ConcreteRoomBuilder::build() {
}
