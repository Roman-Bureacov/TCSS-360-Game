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
 * This struct holds the stats of basic NPCS
 */
struct NPCStats {

    /**This is the time the NPC takes to attack. */
    static const inline int MYNPCATTACKTIME = 10;

    /**This is the name of the goblin. */
    static const inline std::string MYGOBLINNAME = "Goblin";
    /**THis is the health of the goblin. */
    static const inline int MYGOBLINMAXHEALTH = 50;
    /**This is the movment speed of the goblin. */
    static const inline int MYGOBLINMOVEMENTSPEED = 50;
    /**This is the damage the goblin. */
    static const inline int MYGOBLINDAMAGE = 1;

    /**The name skeleton. */
    static const inline std::string MYSKELETONNAME = "Skeleton";
    /**The health of the skeleton. */
    static const inline int MYSKELETONMAXHEALTH = 100;
    /**The movement speed of the skeleton. */
    static const inline int MYSKELETONMOVEMENTSPEED = 10;
    /**The is the damage the skeleton does.  */
    static const inline int MYSKELETONDAMAGE = 2;

    /** The name of the boss character. */
    static const inline std::string MYBOSSNAME = "DarkLord Capual";
    /** The maximum health of Tim Capaul. */
    static const inline int MYBOSSMAXHEALTH = 1000;
    /** The movement speed of Tim Capaul. */
    static const inline int MYBOSSMOVEMENTSPEED = 10;
    /**The is the damage the Tim Capual does.  */
    static const inline int MYBOSSDAMAGE = 10;

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
    Hitbox myNPCWeaponHitbox = Hitbox(100, 100);
    /**Just a simple hitbox for the NPC*/
    Hitbox myNPCHitBox = Hitbox(100, 100);


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
    Goblin(const std::string& theName
            , int theMaxHealth, int theMovementSpeed);

private:
    /** The name of the goblin. */
    std::string myName;
    /** The maximum health of the goblin. */
    int myMaxHealth;
    /** The movement speed of the goblin. */
    int myMovementSpeed;
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
    TimCapaul(const std::string& theName
        , int theMaxHealth, int theMovementSpeed);

private:

    /** The name of the Tim. */
    std::string myName;
    /** The maximum health of the Tim. */
    int myMaxHealth;
    /** The movement speed of the Tim. */
    int myMovementSpeed;


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
    std::string myName;
    /** The maximum health of the skeleton. */
    int myMaxHealth;
    /** The movement speed of the skeleton. */
    int myMovementSpeed;
};

#endif // NPC_H

