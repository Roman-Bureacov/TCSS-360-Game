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
#include "Interactable.h"


/**These are forward declarations to stop circular
 * Dependencies.
 */
class Dungeon;
class Room;

/**
 * Bitz, the engine of the game. Static class that handles when real-time events should occur
 *
 * @author Roman Bureacov, Riley Hopper
 * @version July 2025
 */
class Bitz final {
    friend class Clock;

    Bitz() = delete;
private:
    /** The list of characters active. */
    static std::unordered_set<std::shared_ptr<AbstractCharacter>> entities;
    static std::unordered_set<Interactable*> interactables;
    /** The queue representing the events to be put into the process queue. */
    static std::unordered_map<const AbstractCharacter*, Event*> eventQueue;
    /** The queue representing the events currently being processed. */
    static std::unordered_map<const AbstractCharacter*, Event*> eventProcessQueue;
    /** The thread lock for the event queue. */
    static std::mutex eventQueueMutex;
    /** The dungeon generator. */
    static Dungeon& dungeonGenerator;
    /** The player character. */
    static std::shared_ptr<AbstractCharacter> player;
    /** the current room instance. */
    static Room* currentRoom;
    /** The units per tile from the dungeon. */
    static constexpr int tileSize = 100;
    /** The side length of the room. */
    static int roomSize;

    /**
     * Processes the enqueued single events and persistent events.
     */
    static void processEvents();

    /**
     * Helper function that adjusts the projection hitbox to be less than that of the other.
     * @param theProjection the projection to set the minimum of
     * @param theIntersection the intersecting hitbox to resize with respect to
     * @param theDirection the direction to resize towards
     */
    static void setMin(const Hitbox* theProjection, const Hitbox& theIntersection, util::Direction theDirection);
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
     * Tells the engine that the character wants to interact and
     * should perform hitbox detection for where they are interacting.
     * @param theCharacter the character than is interacting
     */
    static void enqueueInteractEvent(AbstractCharacter* theCharacter);

    /**
     * Enqueues a movement event for the character provided that will attempt to move
     * them in the amount of space desired. The engine will perform collision and boundary
     * checks accordingly and move the character appropriately.
     * @param theCharacter the character that is trying to move
     * @param theDesiredForward the amount the character should move, may be positive or negative
     */
    static void enqueueMovementEvent(AbstractCharacter* theCharacter, int theDesiredForward);

    /**
     * Registers a character with the engine to make it aware of said
     * character when it comes to hitbox detection.
     * @param theCharacter the character that the engine should be aware of
     */
    static void registerCharacter(std::shared_ptr<AbstractCharacter> theCharacter);

    /**
     * Registers a character as the main player into the engine.
     * @param theCharacter the character that will act as the player
     */
    static void registerPlayer(std::shared_ptr<AbstractCharacter> theCharacter);

    /**
     * Registers an interactable that may be used in events.
     * @param theInteractable hte interactable to register
     */
    static void registerInteractable(Interactable* theInteractable);

    /**
     * loads the dungeon room into the engine.
     * @param theRoomID the new room to load.
     */
    static void loadDungeonRoom(int theRoomID);

    /**
     * Retrieves characters that have been registered with the engine.
     * @return the set of character entities registered with the engine
     */
    static const std::unordered_set<std::shared_ptr<AbstractCharacter>>& getEntities();

    /**
     * Retrieves interactable objects that have been registered with the engine.
     * @return the set of interactables registered with the engine
     */
    static const std::unordered_set<Interactable*>& getInteractables();
};

#endif //ENG_H
