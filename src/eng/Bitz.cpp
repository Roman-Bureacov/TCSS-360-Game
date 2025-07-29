//
// Created by iwant on 7/1/2025.
//

#include "Bitz.h"

#include <iostream>

std::list<AbstractCharacter*> entities;
std::list<AbstractCharacter*> persistentEventQueueEntities;
std::list<Event*> Bitz::eventQueue;
std::list<Event*> Bitz::eventProcessQueue;
std::mutex Bitz::eventQueueMutex;

void Bitz::processEvents() {
    std::lock_guard lock(eventQueueMutex);

    // put all the events into the queue for processing
    for (auto iter = eventQueue.begin(); iter != eventQueue.end(); ) {
        // put all the events into the queue
        eventProcessQueue.push_back(*iter);
        iter = eventQueue.erase(iter);
    }

    // process the events
    for (auto iter = eventProcessQueue.begin();
            iter != eventProcessQueue.end() && !eventProcessQueue.empty(); ) {
        const Event* e = *iter;
        e->eventTickCount--;
        e->eventAction();
        if (e->eventTickCount == 0) {
            iter = eventProcessQueue.erase(iter);
            delete e;
        } else ++iter;
    }

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

