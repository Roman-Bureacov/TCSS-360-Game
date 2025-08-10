//
// Created by iwant on 7/1/2025.
//

#ifndef ENG_H
#define ENG_H

#include <functional>
#include <mutex>
#include <unordered_set>

#include "Event.h"
#include "AbstractCharacter.h"
#include "Dungeon.h"


/**
 * Bitz, the engine of the game. Static class that handles when real-time events should occur
 *
 * @author Roman Bureacov
 * @version July 2025
 */
class Bitz final {
    friend class Clock;

    Bitz() = delete;
private:
    /** The list of characters active. */
    static std::unordered_set<AbstractCharacter*> entities;
    /** The queue representing the events to be put into the process queue. */
    static std::unordered_map<const AbstractCharacter*, Event*> eventQueue;
    /** The queue representing the events currently being processed. */
    static std::unordered_map<const AbstractCharacter*, Event*> eventProcessQueue;
    /** The thread lock for the event queue. */
    static std::mutex eventQueueMutex;
    /** The dungeon generator. */
    static Dungeon& dungeonGenerator;
    /** The player character. */
    static AbstractCharacter* player;

    /**
     * Processes the enqueued single events and persistent events.
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

    /**
     * Tells the engine that the character wants to attack and perform
     * hitbox detection their weapons.
     * <br>
     * Friendly fire beware.
     * @param theCharacter the character that is requesting the attack
     */
    static void enqueueAttackEvent(AbstractCharacter* theCharacter);

    /**
     * Registers a character with the engine to make it aware of said character.
     * Will free the memory of the previous character.
     * @param theCharacter the character that the engine should be aware of
     */
    static void registerCharacter(AbstractCharacter* theCharacter);

    /**
     * Registers a character as the main player into the engine.
     * @param theCharacter the character that will act as the player
     */
    static void registerPlayer(AbstractCharacter* theCharacter);

    /**
     * loads the dungeon room into the engine.
     * @param theRoomID the new room to load and its entities
     */
    static void loadDungeonRoom(int theRoomID);
};

#endif //ENG_H
