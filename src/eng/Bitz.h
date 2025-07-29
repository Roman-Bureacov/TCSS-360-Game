//
// Created by iwant on 7/1/2025.
//

#ifndef ENG_H
#define ENG_H

#include <functional>
#include <mutex>
#include <unordered_set>
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
    /** The list of characters active. */
    static std::unordered_set<AbstractCharacter*> entities;
    /** The characters who have an event in queue. */
    static std::list<AbstractCharacter*> lockedEventCharacters;
    /** The queue representing the events to be put into the process queue. */
    static std::list<Event*> eventQueue;
    /** The queue representing the events currently being processed. */
    static std::list<Event*> eventProcessQueue;
    static std::mutex eventQueueMutex;

    /**
     * Processes the enqueued events, and adds them to the persistent events as necessary.
     * Also processes persistent events as well.
     */
    static void processEvents();

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
