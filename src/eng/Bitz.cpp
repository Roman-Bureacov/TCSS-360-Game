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
        e->EVENTACTION();
        if (e->eventTickCount == 0) {
            iter = eventProcessQueue.erase(iter);
            delete e;
        } else ++iter;

    }

}

void Bitz::enqueueEvent(Event* theEvent) {
    std::lock_guard lock(eventQueueMutex);

    const AbstractCharacter *originChar = &(theEvent->EVENTORIGINCHARACTER);

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
                    if (ptr && theCharacter) {
                        return ptr.get() == theCharacter;
                    }

                });

            if (it == entities.end()) return;

            auto c = entities.extract(it);

            const Weapon w = theCharacter->getWeapon();
            const Hitbox h = theCharacter->getAttackHitbox();

            // check for any and all intersections
            for (const auto character : entities) {
                //Checking if the character is a player or NPC
                auto npc = std::dynamic_pointer_cast<NPC>(character);
                auto player = std::dynamic_pointer_cast<Player>(character);

                if (player && h.intersects(character->getHitbox())) {
                    character->damage(w.getModifiedDamage());
                } if (npc && npc->getIsActive()
                    && h.intersects(character->getHitbox())) {
                    character->damage(w.getModifiedDamage());
                }
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


            const util::Direction d = theCharacter->getDirection();


            switch (d) {
                case util::NORTH:
                    // define deltaY
                    projY = theCharacter->getY() + theCharacter->getHitbox().getHeight();
                    projWidth = theCharacter->getHitbox().getWidth();
                    projHeight = theDesiredForward;
                    break;
                case util::EAST:
                    // define deltaX
                    projX = theCharacter->getX() + theCharacter->getHitbox().getWidth();
                    projWidth = theDesiredForward;
                    projHeight = theCharacter->getHitbox().getHeight();
                    break;
                case util::SOUTH:
                    projY -= theDesiredForward;
                    projWidth = theCharacter->getHitbox().getWidth();
                    projHeight = theDesiredForward;
                    break;
                case util::WEST:
                    projX -= theDesiredForward;
                    projWidth = theDesiredForward;
                    projHeight = theCharacter->getHitbox().getHeight();
                    break;
                default: throw new std::logic_error("Unknown direction enum");


            }


            // adjust parameters to fit the room
            projX = std::max(Room::TILESIZE, projX);
            projY = std::max(Room::TILESIZE, projY);
            projWidth = std::min((Room::ROOMSIZE - 1) * Room::TILESIZE - projX, projWidth);
            projHeight = std::min((Room::ROOMSIZE - 1) * Room::TILESIZE - projY, projHeight);
            // create the projection

            Hitbox* projection = new Hitbox(projX, projY, projWidth, projHeight);


            // find the minimum possible distance to travel
            // find the intersections
            // first extract the entity (it shouldn't collide with itself)
            auto benchedCharacter = [theCharacter] {
                auto it = std::find_if(entities.begin(), entities.end(),
                [theCharacter](const std::shared_ptr<AbstractCharacter>& ptr) {
                    return ptr.get() == theCharacter;
                });

                return entities.extract(it);
            }(); // immediately invoke lambda

            for (const std::shared_ptr<AbstractCharacter> c : entities) {

                auto npc = std::dynamic_pointer_cast<NPC>(c);

                if (npc && npc->getIsActive() && projection->intersects(c->getHitbox())) {
                    setMin(projection, c->getHitbox(), d);
                }
            }

            for (const Interactable* i : interactables) {
                if (projection->intersects((i->getHitbox()))) {
                    setMin(projection, i->getHitbox(), d);
                }
            }

            entities.insert(std::move(benchedCharacter));

            // position character appropriately
            switch (d) {
                case util::NORTH:
                    // the projection height is a deltaY
                    theCharacter->setY(theCharacter->getY() + projection->getHeight());
                    break;
                case util::EAST:
                    // the projection width is a deltaX
                    theCharacter->setX(theCharacter->getX() + projection->getWidth());
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

void Bitz::setMin(Hitbox*& theProjection, const Hitbox &theIntersection, const util::Direction theDirection) {
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
            minHeight = theIntersection.getOrigin().y - minY;
            break;
        case util::EAST:
            minWidth = theIntersection.getOrigin().x - minX;

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
            break;
        default: throw new std::logic_error("Unknown direction enum");
    }

    delete theProjection;
    theProjection = new Hitbox(minX, minY, minWidth, minHeight);
}

void Bitz::clearEntities() {
    entities.clear();
}

void Bitz::clearEventQueue() {
    eventQueue.clear();
    eventProcessQueue.clear();
}

void Bitz::clearInteractables() {
    interactables.clear();
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
    entities.insert(theCharacter);
}

void Bitz::registerInteractable(Interactable *theInteractable) {
    interactables.insert((theInteractable));
}

void Bitz::loadDungeonRoom(const util::Direction theMoveDirection) {


    util::Direction comingFrom = theMoveDirection;
    int nextRoom;

    // cleanup
    eventQueue.clear();
    eventProcessQueue.clear();

    switch (theMoveDirection) {
        case util::NORTH:
            nextRoom = dungeonGenerator.getCurrentRoom()->getRoomID()
                - Dungeon::ROOMVERTICALIDCHANGE;
            break;
        case util::SOUTH:
            nextRoom = dungeonGenerator.getCurrentRoom()->getRoomID()
                + Dungeon::ROOMVERTICALIDCHANGE;
            break;
        case util::EAST:
            nextRoom = dungeonGenerator.getCurrentRoom()->getRoomID()
                + Dungeon::ROOMHORIZONTALIDCHANGE;
            break;
        case util::WEST:
            nextRoom = dungeonGenerator.getCurrentRoom()->getRoomID()
                - Dungeon::ROOMHORIZONTALIDCHANGE;
            break;
        default:
            nextRoom = dungeonGenerator.getCurrentRoom()->getRoomID();
    }

    //Changes the room and makes sure the room change was valid.
    if (!dungeonGenerator.setCharacterRoom(nextRoom)) {
        std::cout << nextRoom << "room isn't within the dungeon!" << std::endl;
        return;
    }
    currentRoom = dungeonGenerator.getCurrentRoom().get();


    constexpr int doorOffset = 50;
    switch (comingFrom) {
        case util::SOUTH:
            player->setY(Room::TILESIZE * 2);
            break;
        case util::WEST:
            player->setX(Room::TILESIZE * (Room::ROOMSIZE - 2));
            break;
        case util::NORTH:
            player->setY(Room::TILESIZE * (Room::ROOMSIZE - 2));
            break;
        case util::EAST:
            player->setX(Room::TILESIZE * 2);
            break;
        default:
            throw std::logic_error("missing handle on direction " + std::to_string(comingFrom));
    }

}

const std::unordered_set<std::shared_ptr<AbstractCharacter>> & Bitz::getEntities() {
    return entities;
}

const std::unordered_set<Interactable *> & Bitz::getInteractables() {
    return interactables;
}
