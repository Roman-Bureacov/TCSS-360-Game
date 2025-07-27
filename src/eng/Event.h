//
// Created by iwant on 7/27/2025.
//

#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <stdexcept>

#include "../include/AbstractCharacter.h"

/**
 * An event struct. Houses a tick count for how long the event
 * will last (1 tick if it is a single-tick, non-persistent event).
 * @author Roman Bureacov
 * @version 2025 July
 */
struct Event {
    long eventTickCount = 1;
    const std::function<void()> eventAction;
    const AbstractCharacter& eventOriginCharacter;

    /**
     * Creates a new event for the engine to process.
     * <br>
     * The for persistent events (where tick count is greater than 1)
     * the engine will loop for however many ticks this event asks for.
     * @param theEventTickCount the number of ticks this event will last
     * @param theEventAction the event to iterate
     * @param theEventOrigin the character that provided this event
     * @throws std::logic_error if theEventTickCount is less than 1
     */
    explicit Event(const long theEventTickCount,
                    const std::function<void()>& theEventAction,
                    const AbstractCharacter& theEventOrigin)
                    : eventAction(theEventAction), eventOriginCharacter(theEventOrigin) {
        if (theEventTickCount < 1) throw std::logic_error("Events cannot have a negative tick count");
        eventTickCount = theEventTickCount;
    }
};

#endif //EVENT_H
