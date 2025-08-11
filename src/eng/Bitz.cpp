//
// Created by iwant on 7/1/2025.
//

#include "../include/Bitz.h"
#include "../include/Dungeon.h"


std::unordered_set<AbstractCharacter*> Bitz::entities;
std::unordered_map<const AbstractCharacter*, Event*> Bitz::eventQueue;
std::unordered_map<const AbstractCharacter*, Event*> Bitz::eventProcessQueue;
std::mutex Bitz::eventQueueMutex;
Dungeon& Bitz::dungeonGenerator = *Dungeon::DungeonInstance();
AbstractCharacter* Bitz::player = nullptr;

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


void Bitz::loadDungeonRoom(const int theRoomID) {
    // cleanup
    eventQueue.clear();
    eventProcessQueue.clear();

    // cleanup entities, store their information in the database
    entities.erase(player);
    for (auto c : entities) {
        // TODO: while clearing entities, store them in the database
        delete c;
    }
    entities.clear();
    entities.insert(player);

    // next room
    dungeonGenerator.setCharacterRoom(theRoomID);

    // position player

}
