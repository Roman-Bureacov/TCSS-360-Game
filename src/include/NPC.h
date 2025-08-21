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

/**
 * This struct holds the stats of basic NPCS
 */
struct NPCStats {
    static const inline std::string goblinName = "Goblin";
    static const inline int goblinMaxHealth = 50;
    static const inline int goblinMovementSpeed = 100;

    static const inline std::string skeletonName = "Skeleton";
    static const inline int skeletonMaxHealth = 100;
    static const inline int skeletonMovementSpeed = 10;

};

class Goblin;
class TimCapaul;
class Skeleton;

/**
 *
 * Base class for all NPC types. Inherits from AbstractCharacter.
 *
 * Handles shared logic such as interaction with player characters,
 * basic combat routines, and event behavior.
 *
 * @author Riley Hopper
 * @version 2025 August
 */
class NPC : public AbstractCharacter {
public:

    /** the property name for when the NPCs activity changes */
    inline static const std::string PROPERTY_ACTIVE_CHANGED = "My activity changed";

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

    void Update(Subject *theChangedSubject, const std::string &thePropertyName) override;

    /**
     * Sets the characters activity level.
     * @param isActive This is the truthy value it will be set to.
     */
    void setIsActive(bool isActive);

    /**
     *
     * @return The truthy value on if the character is active.
     */
    bool getIsActive();

    /**
     * Protected constructor used by derived NPCs.
     * @param theName NPC's display name
     * @param theMaxHealth Maximum health
     * @param theMovementSpeed Base movement speed
     */
    NPC(const std::string& theName
        , int theMaxHealth, int theMovementSpeed);

    /**
     * sets the player pointer
     * @param thePlayer This is a pointer to the player.
     */
    void setPlayer(std::shared_ptr<AbstractCharacter> thePlayer);



protected:


    /**
     * Pointer to the player. Used for NPC decision-making.
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
    bool canAttack();

    /**
     * This makes tells the NPC to changes its
     * Direction to look at the player.
     */
    void lookAtPlayer();

    /**This is if the NPC is active*/
    bool active = false;

    /**Just a basic hitbox for the weapon.*/
    Hitbox NPCWeaponHitbox = Hitbox(100, 100);
    /**Just a simple hitbox for the NPC*/
    Hitbox NPCHitBox = Hitbox(100, 100);


};

/**
 * Goblin NPC class.
 * Fast-moving, weak enemy with basic AI.
 */
class Goblin : public NPC {
public:
    /**
     * Constructs a Goblin NPC.
     * @param theName The name of the goblin.
     * @param theMaxHealth The maximum health value.
     * @param theMovementSpeed The movement speed value.
     */
    Goblin(const std::string& theName, int theMaxHealth, int theMovementSpeed);

private:
    /** The name of the goblin. */
    std::string name;
    /** The maximum health of the goblin. */
    int maxHealth;
    /** The movement speed of the goblin. */
    int movementSpeed;
};

/**
 * Tim Capaul NPC class.
 * Unique boss-type character with custom behavior.
 */
class TimCapaul : public NPC {
public:
    /**
     * Constructs the Tim Capaul boss NPC.
     * Initializes with predefined stats and name.
     */
    TimCapaul();

    /**
     * Executes Tim Capaul's custom behavior each tick.
     * Overrides base NPC action logic.
     */
    void takeAction() override;

private:
    /** The name of the boss character. */
    static const inline std::string name = "DarkLord Capual";
    /** The maximum health of Tim Capaul. */
    static constexpr int maxHealth = 1000;
    /** The movement speed of Tim Capaul. */
    static constexpr int movementSpeed = 10;

    /**
     * Moves Tim Capaul toward the player.
     * Used as part of his AI behavior.
     */
    void moveNPCToPlayer();

    /**
     * Executes an attack on the player.
     * Called when within range and conditions are met.
     */
    void attackPlayer();

    /**
     * Determines if Tim Capaul can attack.
     * Based on proximity and cooldown logic.
     * @return True if attack is possible, false otherwise.
     */
    bool canAttack();
};

/**
 * Skeleton NPC class.
 * Balanced enemy type with standard AI shared from base NPC class.
 */
class Skeleton : public NPC {
public:
    /**
     * Constructs a Skeleton NPC.
     * @param theName The name of the skeleton.
     * @param theMaxHealth The maximum health value.
     * @param theMovementSpeed The movement speed value.
     */
    Skeleton(const std::string& theName, int theMaxHealth, int theMovementSpeed);

private:
    /** The name of the skeleton. */
    std::string name;
    /** The maximum health of the skeleton. */
    int maxHealth;
    /** The movement speed of the skeleton. */
    int movementSpeed;
};

#endif // NPC_H

