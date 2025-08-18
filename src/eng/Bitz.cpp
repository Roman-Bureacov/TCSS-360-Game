//
// Created by iwant on 7/1/2025.
//

#include "../include/Bitz.h"

#include "../include/Door.h"
#include "../include/Dungeon.h"


std::shared_ptr<AbstractCharacter> Bitz::player = nullptr;
std::unordered_set<std::shared_ptr<AbstractCharacter>> Bitz::entities;
std::unordered_set<Interactable*> Bitz::interactables;
std::unordered_map<const AbstractCharacter*, Event*> Bitz::eventQueue;
std::unordered_map<const AbstractCharacter*, Event*> Bitz::eventProcessQueue;
std::mutex Bitz::eventQueueMutex;
Dungeon& Bitz::dungeonGenerator = *Dungeon::DungeonInstance();
Room* Bitz::currentRoom;

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
            auto it = std::find_if(entities.begin(), entities.end(),
                [theCharacter](const std::shared_ptr<AbstractCharacter>& ptr) {
                    return ptr.get() == theCharacter;
                });

            if (it == entities.end()) return;

            auto c = entities.extract(it);

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

void Bitz::enqueueMovementEvent(AbstractCharacter *theCharacter, int theDesiredForward) {
    if (theDesiredForward < 0) {
        util::Direction originalDirection = theCharacter->getDirection();
        switch (originalDirection) {
            case util::NORTH:
                theCharacter->setDirection(util::SOUTH);
                break;
            case util::EAST:
                theCharacter->setDirection(util::WEST);
                break;
            case util::SOUTH:
                theCharacter->setDirection(util::NORTH);
                break;
            case util::WEST:
                theCharacter->setDirection(util::EAST);
                break;
            default: throw new std::logic_error("Unknown direction enum");
        }
        enqueueMovementEvent(theCharacter, -theDesiredForward);
        theCharacter->setDirection(originalDirection);
        return;
    }

    enqueueEvent(new Event(
        1,
        [theCharacter, theDesiredForward]() -> void {
            // create a projection of the movement
            int projWidth;
            int projHeight;
            int projX = theCharacter->getX();
            int projY = theCharacter->getY();

            int desiredForward = std::abs(theDesiredForward);

            const util::Direction d = theCharacter->getDirection();


            switch (d) {
                case util::NORTH:
                    projWidth = theCharacter->getHitbox().getWidth();
                    projHeight = desiredForward;
                    break;
                case util::EAST:
                    projWidth = desiredForward;
                    projHeight = theCharacter->getHitbox().getHeight();
                    break;
                case util::SOUTH:
                    projY -= theDesiredForward;
                    projWidth = theCharacter->getHitbox().getWidth();
                    projHeight = desiredForward;
                    break;
                case util::WEST:
                    projX -= theDesiredForward;
                    projWidth = desiredForward;
                    projHeight = theCharacter->getHitbox().getHeight();
                    break;
                default: throw new std::logic_error("Unknown direction enum");
            }


            // adjust parameters to fit the room
            projX = std::max(0, projX);
            projY = std::max(0, projY);
            projWidth = std::min(Room::roomSize * Room::tileSize - projX, projWidth);
            projHeight = std::min(Room::roomSize * Room::tileSize - projY, projHeight);
            // create the projection

            std::cout << projX << ' ' << projY << ' ' << projWidth << ' ' << projHeight <<   std::endl;
            Hitbox* projection = new Hitbox(projX, projY, projWidth, projHeight);
            std::cout << "Here"<< std::endl;

            // find the minimum possible distance to travel
            // find the intersections
            for (const std::shared_ptr<AbstractCharacter> c : entities) {
                if (projection->intersects(c->getHitbox())) {
                    setMin(projection, c->getHitbox(), d);
                }
            }
            for (const Interactable* i : interactables) {
                if (projection->intersects((i->getHitbox()))) {
                    setMin(projection, i->getHitbox(), d);
                }
            }

            // position character appropriately
            switch (d) {
                case util::NORTH:
                    theCharacter->setY(
                        projection->getOrigin().y
                        + theCharacter->getHitbox().getHeight() - projection->getHeight()
                    );
                    break;
                case util::EAST:
                    theCharacter->setX(
                        projection->getOrigin().x
                        + theCharacter->getHitbox().getWidth() - projection->getWidth()
                    );
                    break;
                case util::SOUTH:
                    theCharacter->setY(projection->getOrigin().y);
                    break;
                case util::WEST:
                    theCharacter->setX(projection->getOrigin().x);
                    break;
                default: throw new std::logic_error("Unknown direction enum");
            }

            // cleanup
            delete projection;
        },
        *theCharacter
    ));
}

void Bitz::setMin(const Hitbox* theProjection, const Hitbox &theIntersection, const util::Direction theDirection) {
    int minX = theProjection->getOrigin().x;
    int minY = theProjection->getOrigin().y;
    int minHeight = theProjection->getHeight();
    int minWidth = theProjection->getWidth();

    int intersectX;
    int intersectY;
    int intersectW;
    int intersectH;
    switch (theDirection) {
        case util::NORTH:
            minHeight = minY - theIntersection.getOrigin().y;
            break;
        case util::EAST:
            minWidth = minX - theIntersection.getOrigin().x;
            break;
        case util::SOUTH:
            intersectY = theIntersection.getOrigin().y;
            intersectH = theIntersection.getHeight();
            minHeight = minHeight - (intersectY + intersectH - minY);
            minY = intersectY + intersectH;
            break;
        case util::WEST:
            intersectX = theIntersection.getOrigin().x;
            intersectW = theIntersection.getWidth();
            minWidth = minWidth - (intersectX + intersectW - minX);
            minX = intersectX + intersectW;
            break;
        default: throw new std::logic_error("Unknown direction enum");
    }
    theProjection = new Hitbox(minX, minY, minWidth, minHeight);
}

void Bitz::registerCharacter(std::shared_ptr<AbstractCharacter> theCharacter) {
    auto npc = std::dynamic_pointer_cast<NPC>(theCharacter);
    if (npc) {
        npc->setPlayer(player);
    }
    entities.insert(theCharacter);

}

void Bitz::registerPlayer(std::shared_ptr<AbstractCharacter> theCharacter) {
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
    //entities.erase(player);
    //dungeonGenerator.updateRoomEntities(entities);
    //entities.clear();
    //entities.insert(player);

    for (auto i : interactables) delete i;
    interactables.clear();

    // next room
    dungeonGenerator.setCharacterRoom(theRoomID);
    currentRoom = dungeonGenerator.getCurrentRoom().get();

    // position NESW doors
    // each room is made of tiles, with 2 tiles serving as walls on both ends
    const int doorWidth = Room::tileSize;
    const int doorDepth = Room::tileSize / 2;
    const int centeredPos = (Room::roomSize - doorWidth)/2;
    const int doorInsetPos = (doorDepth / 2);
    if (currentRoom->getNorth())
        registerInteractable(new Door(
            Hitbox(centeredPos, Room::roomSize - doorInsetPos, doorWidth, doorDepth),
            theRoomID - 10
            ));
    if (currentRoom->getEast())
        registerInteractable(   new Door(
            Hitbox(Room::roomSize - doorInsetPos, centeredPos, doorDepth, doorWidth),
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
    const int centeredPlayerX = (Room::roomSize - player->getHitbox().getWidth()) / 2;
    const int centeredPlayerY = (Room::roomSize - player->getHitbox().getHeight()) / 2;
    constexpr int doorOffset = 50;
    switch (comingFrom) {
        case util::NORTH:
            player->setX(centeredPlayerX);
            player->setY(Room::roomSize - doorInsetPos - doorOffset);
            break;
        case util::EAST:
            player->setX(Room::roomSize - doorInsetPos - doorOffset);
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
    //for (const auto& character : currentRoom->getCharacters())
    //    registerCharacter(character.get());
}

const std::unordered_set<std::shared_ptr<AbstractCharacter>> & Bitz::getEntities() {
    return entities;
}

const std::unordered_set<Interactable *> & Bitz::getInteractables() {
    return interactables;
}
