//
// Created by iwant on 7/1/2025.
//

#include "Bitz.h"

std::list<AbstractCharacter*> entities;
std::list<AbstractCharacter*> persistentEventQueueEntities;
std::list<Event*> Bitz::eventQueue;
std::list<Event*> Bitz::singleEventQueue;
std::list<Event*> Bitz::persistentEventQueue;


void Bitz::processEvents() {
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
    for (const Event* event : singleEventQueue) event->eventAction();

    // then process the persistent events
    for (const Event* event : persistentEventQueue) event->eventAction();
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
    // get reference of pointer, that way the pointer can be reassigned
    for (Event*& event : eventQueue) {
        if (event->eventOriginCharacter.getID() == theEvent->eventOriginCharacter.getID()) {
            event = theEvent;
            return;
        }
    }
    eventQueue.push_back(theEvent);
}

