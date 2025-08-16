//
// Created by riley on 8/9/25.
//

#ifndef NPC_H
#define NPC_H

#include <memory>
#include <iostream>
#include "AbstractCharacter.h"
#include "../include/Bitz.h"


/**
 * Enumeration of all supported NPC types.
 */
enum class NPCType {
    Skeleton,
    Goblin,
    TimCapaul
};


class Goblin;
class TimCapaul;
class Skeleton;

/**
 * Base class for all NPC types. Inherits from AbstractCharacter.
 *
 * Handles shared logic such as interaction with player characters,
 * basic combat routines, and event behavior.
 *
 * @author Riley Hopper
 */
class NPC : public AbstractCharacter {
public:
    /**
     * Factory method to create a Goblin NPC.
     * @return Shared pointer to a new Goblin instance.
     */
    static std::shared_ptr<Goblin> goblinFactory();

    /**
     * Factory method to create Tim Capaul, the dark lord.
     * @return Shared pointer to a new TimCapaul instance.
     */
    static std::shared_ptr<TimCapaul> timCapaulFactory();

    /**
     * Factory method to create a Skeleton NPC.
     * @return Shared pointer to a new Skeleton instance.
     */
    static std::shared_ptr<Skeleton> skeletonFactory();

    /**
     * Executes the NPC's logic during its turn.
     * Must be overridden by derived classes.
     */
    virtual void takeAction();

    /**
     * Sets if the NPC is active
     */
    void setActive(bool act);

protected:
    /**
     * Protected constructor used by derived NPCs.
     * @param theName NPC's display name
     * @param theMaxHealth Maximum health
     * @param theMovementSpeed Base movement speed
     */
    NPC(const std::string& theName, int theMaxHealth, int theMovementSpeed);

    /**
     * Pointer to the player. Used for NPC decision making.
     */
    std::shared_ptr<AbstractCharacter> player;

    /**
     * Moves the NPC toward the player.
     */
    void moveNPCToPlayer();

    /**
     * Performs an attack on the player, if in range.
     */
    void attackPlayer();

    /**
     * Checks if the player is in range to be attacked.
     * @return True if the NPC can attack the player this turn.
     */
    bool canAttack() const;

    /**
     * This makes tells the NPC to changes its
     * Direction to look at the player.
     */
    void lookAtPlayer();

    bool active = false;

};

/**
 * Goblin NPC class.
 * Fast-moving, weak enemy with basic AI.
 */
class Goblin : public NPC {
public:
    Goblin();

private:
    static const inline std::string name = "Goblin";
    static constexpr int maxHealth = 50;
    static constexpr int movementSpeed = 10;
};

/**
 * Tim Capaul NPC class.
 * Unique boss-type character with custom behavior.
 */
class TimCapaul : public NPC {
public:
    TimCapaul();
    void takeAction() override;

private:
    static const inline std::string name = "DarkLord Capual";
    static constexpr int maxHealth = 1000;
    static constexpr int movementSpeed = 10;

    void moveNPCToPlayer();
    void attackPlayer();
    bool canAttack();
};

/**
 * Skeleton NPC class.
 * Balanced enemy type with standard AI shared from base NPC class.
 */
class Skeleton : public NPC {
public:
    Skeleton();

private:
    static const inline std::string name = "Skeleton";
    static constexpr int maxHealth = 100;
    static constexpr int movementSpeed = 10;
};

#endif // NPC_H
