//
// Created by iwant on 7/1/2025.
//

#ifndef ENG_H
#define ENG_H

#include <functional>
#include <vector>

#include "Event.h"
#include "../include/AbstractCharacter.h"


/**
 * Bitz, the engine of the game. Static class that handles when real-time events should occur
 *
 * @author Roman Bureacov
 * @version July 2025
 */
class Bitz {
    friend class Clock;

    Bitz() = delete;
private:
    static std::list<AbstractCharacter*> entities;
    static std::list<AbstractCharacter*> persistentEventQueueEntities;
    static std::list<Event*> eventQueue;
    static std::list<Event*> persistentEventQueue;

    /**
     * Processes the enqueued events, and adds them to the persistent events as necessary.
     * Also processes persistent events as well.
     */
    static void processEvents();

    /**
     * enqueues persistent events, events that lock characters into an event until its completion.
     * @param theEvent the persistent event to enqueue
     */
    static void enqueuePersistentEvent(Event* theEvent);
public:
    /**
     * Enqueues an event to occur in the next engine tick.
     * <br>
     * Character are limited to enqueue only one event at a time.
     * Attempting to enqueue another event will overwrite the currently-stored event
     * by that character.
     * @param theEvent event to enqueue.
     */
    static void enqueueEvent(Event* theEvent);
};

#endif //ENG_H
