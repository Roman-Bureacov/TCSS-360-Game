//
// Created by iwant on 7/1/2025.
//

#include "../include/Bitz.h"

#include "../app/model/Enviroment/Door.h"
#include "../include/Dungeon.h"


AbstractCharacter* Bitz::player = nullptr;
std::unordered_set<AbstractCharacter*> Bitz::entities;
std::unordered_set<Interactable*> Bitz::interactables;
std::unordered_map<const AbstractCharacter*, Event*> Bitz::eventQueue;
std::unordered_map<const AbstractCharacter*, Event*> Bitz::eventProcessQueue;
std::mutex Bitz::eventQueueMutex;
Dungeon& Bitz::dungeonGenerator = *Dungeon::DungeonInstance();
Room* Bitz::currentRoom;
int Bitz::roomSize;

void Bitz::processEvents() {
    std::lock_guard lock(eventQueueMutex);

    // put all the events into the queue for processing
    for (auto iter = eventQueue.begin(); iter != eventQueue.end();) {
        eventProcessQueue[iter->first] = iter->second;
        iter = eventQueue.erase(iter);
    }

    // process the events
    for (auto iter = eventProcessQueue.begin();
            iter != eventProcessQueue.end(); ) {
        // extract the event from the map
        const Event* e = iter->second;

        // process
        e->eventTickCount--;
        e->eventAction();
        if (e->eventTickCount == 0) {
            iter = eventProcessQueue.erase(iter);
            delete e;
        } else ++iter;

    }

}

void Bitz::enqueueEvent(Event* theEvent) {
    std::lock_guard lock(eventQueueMutex);

    const AbstractCharacter *originChar = &(theEvent->eventOriginCharacter);

    // if the character has an event active in the process queue, ignore the request
    if (eventProcessQueue.contains(originChar)) {
        delete theEvent;
        return;
    }

    // if the character already asked for an event to be queued, replace it
    auto iter = eventQueue.find(originChar);
    if (iter != eventQueue.end()) {
        delete iter->second;
        iter->second = theEvent;
        return;
    }

    // brand-new event, append it
    eventQueue[originChar] = theEvent;
}

void Bitz::enqueueAttackEvent(AbstractCharacter *theCharacter) {
    enqueueEvent(new Event(
        theCharacter->getWeapon().attackTicks,
        [theCharacter]() -> void {
            auto c = entities.extract(theCharacter);
            const Weapon w = theCharacter->getWeapon();
            const Hitbox h = theCharacter->getAttackHitbox();

            // check for any and all intersections
            for (const auto character : entities) {
                if (h.intersects(character->getHitbox()))
                    character->damage(w.getModifiedDamage());
            }
            entities.insert(std::move(c));
        },
        *theCharacter
    ));
}

void Bitz::enqueueInteractEvent(AbstractCharacter *theCharacter) {
    enqueueEvent(new Event(
        1,
        [theCharacter]() -> void {
            const Hitbox h = theCharacter->getInteractionHitbox();

            for (const auto interactable : interactables) {
                if (h.intersects(interactable->getHitbox()))
                    interactable->interact();
            }
        },
        *theCharacter
        ));
}

void Bitz::registerCharacter(AbstractCharacter* theCharacter) {
    entities.insert(theCharacter);
}

void Bitz::registerPlayer(AbstractCharacter *theCharacter) {
    if (entities.contains(player)) entities.erase(player);
    delete player;
    registerCharacter(theCharacter);
    player = theCharacter;
}

void Bitz::registerInteractable(Interactable *theInteractable) {
    interactables.insert((theInteractable));
}

void Bitz::loadDungeonRoom(const int theRoomID) {
    // get current room code to infer where we are coming from
    const int dif = theRoomID - currentRoom->getRoomID();
    util::Direction comingFrom;
    switch (dif) {
        case 1: comingFrom = util::WEST; break;
        case -1: comingFrom = util::EAST; break;
        case 10: comingFrom = util::NORTH; break;
        case -10: comingFrom = util::SOUTH; break;
        default: throw std::logic_error("Unknown room ID translation" + dif);
    }

    // cleanup
    eventQueue.clear();
    eventProcessQueue.clear();

    // cleanup entities, store their information in the database
    entities.erase(player);
    dungeonGenerator.updateRoomEntities(entities);
    entities.clear();
    entities.insert(player);

    for (auto i : interactables) delete i;
    interactables.clear();

    // next room
    dungeonGenerator.setCharacterRoom(theRoomID);
    currentRoom = dungeonGenerator.getCurrentRoom().get();
    roomSize = (currentRoom->getRoomSize() - 2) * tileSize;

    // position NESW doors
    // each room is made of tiles, with 2 tiles serving as walls on both ends
    const int doorWidth = tileSize;
    const int doorDepth = tileSize / 2;
    const int centeredPos = (roomSize - doorWidth)/2;
    const int doorInsetPos = (doorDepth / 2);
    if (currentRoom->getNorth())
        registerInteractable(new Door(
            Hitbox(centeredPos, roomSize - doorInsetPos, doorWidth, doorDepth),
            theRoomID - 10
            ));
    if (currentRoom->getEast())
        registerInteractable(   new Door(
            Hitbox(roomSize - doorInsetPos, centeredPos, doorDepth, doorWidth),
            theRoomID + 1));
    if (currentRoom->getSouth())
        registerInteractable(new Door(
            Hitbox(centeredPos, -doorInsetPos, doorWidth, doorDepth),
            theRoomID + 10));
    if (currentRoom->getWest())
        registerInteractable(new Door(
            Hitbox(-doorInsetPos, centeredPos, doorDepth, doorWidth),
            theRoomID - 1));

    // position player
    const int centeredPlayerX = (roomSize - player->getHitbox().getWidth()) / 2;
    const int centeredPlayerY = (roomSize - player->getHitbox().getHeight()) / 2;
    constexpr int doorOffset = 50;
    switch (comingFrom) {
        case util::NORTH:
            player->setX(centeredPlayerX);
            player->setY(roomSize - doorInsetPos - doorOffset);
            break;
        case util::EAST:
            player->setX(roomSize - doorInsetPos - doorOffset);
            player->setY(centeredPlayerY);
            break;
        case util::SOUTH:
            player->setX(centeredPlayerX);
            player->setY(doorInsetPos + doorOffset);
            break;
        case util::WEST:
            player->setX(doorInsetPos + doorOffset);
            player->setY(centeredPlayerY);
            break;
        default: throw std::logic_error("missing handle on direction " + comingFrom);
    }

    // position others
    for (const auto& character : currentRoom->getCharacters())
        registerCharacter(character.get());
}

const std::unordered_set<AbstractCharacter *> & Bitz::getEntities() {
    return entities;
}

const std::unordered_set<Interactable *> & Bitz::getInteractables() {
    return interactables;
}
