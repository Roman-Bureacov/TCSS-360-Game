//
// Created by iwant on 7/1/2025.
//

#include "Bitz.h"

#include <iostream>

std::list<AbstractCharacter*> entities;
std::list<AbstractCharacter*> persistentEventQueueEntities;
std::list<Event*> Bitz::eventQueue;
std::list<Event*> Bitz::singleEventQueue;
std::list<Event*> Bitz::persistentEventQueue;
std::mutex Bitz::eventQueueMutex;

void Bitz::processEvents() {
    std::lock_guard lock(eventQueueMutex);

    for (auto iter = eventQueue.begin(); iter != eventQueue.end(); ) {
        // persistent events are ones with a tick count greater than 1
        if (Event* event = *iter; event->eventTickCount > 1) { // if-init-statement
            // throw it into the persistent event queue
            persistentEventQueue.push_back(event);
        } else {
            // throw it into the single event queue
            singleEventQueue.push_back(event);
        }
        iter = eventQueue.erase(iter);
    }

    // process the non-persistent events first
    for (auto iter = singleEventQueue.begin();
            iter != singleEventQueue.end() && !singleEventQueue.empty(); ) {
        const Event* e = *iter;
        e->eventAction();
        iter = singleEventQueue.erase(iter);
    }

    // then process the persistent events
    for (auto iter = persistentEventQueue.begin();
            iter != persistentEventQueue.end() && !persistentEventQueue.empty(); ) {
        const Event* e = *iter;
        e->eventTickCount--;
        e->eventAction();
        if (e->eventTickCount == 0) iter = persistentEventQueue.erase(iter);
    }
    std::cout << "A" << std::endl;
}

void Bitz::enqueuePersistentEvent(Event* theEvent) {
    for (Event*& event : persistentEventQueue) {
        if (event->eventOriginCharacter.getID() == theEvent->eventOriginCharacter.getID()) {
            event = theEvent;
            return;
        }
    }
    eventQueue.push_back(theEvent);
}

void Bitz::enqueueEvent(Event* theEvent) {
    //std::lock_guard lock(eventQueueMutex); // TODO: is this necessary?
    // get reference of pointer, that way the pointer can be reassigned
    for (Event*& event : eventQueue) {
        if (event->eventOriginCharacter.getID() == theEvent->eventOriginCharacter.getID()) {
            delete event;
            event = theEvent;
            return;
        }
    }
    eventQueue.push_back(theEvent);
}

