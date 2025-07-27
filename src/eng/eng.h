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
 * Bitz, the engine of the game.
 *
 * @author Roman Bureacov
 * @version July 2025
 */
class eng {
private:
    std::list<AbstractCharacter&> entities;
    std::list<AbstractCharacter&> persistentEventQueueEntities;
    std::list<Event&> eventQueue;
    std::list<Event&> persistentEventQueue;

    /**
     * Processes the enqueued events, and adds them to the persistent events as necessary.
     * Also processes persistent events as well.
     */
    void processEvents();

    /**
     * enqueues persistent events, events that lock characters into a move
     * @param theEvent the persistent event to enqueue
     */
    void enqueuePersistentEvent(Event& theEvent);
public:
    /**
     * Enqueues an event to occur in the next engine tick.
     * <br>
     * Character are limited to enqueue only one event at a time.
     * Attempting to enqueue another event will overwrite the currently-stored event
     * by that character.
     * @param theEvent event to enqueue.
     */
    void enqueueEvent(Event& theEvent);
};

#endif //ENG_H
