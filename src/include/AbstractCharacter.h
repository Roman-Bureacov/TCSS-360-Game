//
// Created by riley on 7/23/25.
//

#ifndef ABSTRACTCHARACTER_H
#define ABSTRACTCHARACTER_H
#include <string>


/**
 * Represents the basic character.
 * @author Riley Hopper
 * @author Roman Bureacov
 * @version 2025 July
 */
class AbstractCharacter {
private:
    const std::string& myName;
    const unsigned long long myID;
    int myHealth = 0;
    int myMaxHealth = 0;
    int myBaseMovement = 0;
    int myCurrentMovement = 0;
public:
    virtual ~AbstractCharacter() = default;

    /**
     * Constructs a character with the stats specified.
     * @param theName the name this character should use
     * @param theMaxHealth the maximum health this character should have
     * @param theMovementSpeed the movement speed this character should have
     */
    AbstractCharacter(const std::string& theName, int theMaxHealth, int theMovementSpeed);

    /**
     * Returns the unique ID that represents this character.
     * @return the unique ID that represents this character
     */
    unsigned int getID() const;

    /**
     * Retrieve the name for this character.
     * @return the name attributed to this character
     */
    const std::string& getName() const;

    /**
     * Asks if this character is alive (might need to call the reaper).
     * @return if the character is alive
     */
    bool isAlive() const;

    /**
     * Set the max health for this character.
     * @param theNewMaxHealth the new max health to set for this character
     * @throws std::logic_error if the new max health is less than 1
     */
    void setMaxHealth(int theNewMaxHealth);

    /**
     * Asks what the maximum health of this character is.
     * @return the maximum health this character can have
     */
    int getMaxHealth() const;

    /**
     * Sets the health for this charcter.
     * @param theNewHealth the new health for this character
     */
    void setHealth(int theNewHealth);

    /**
     * Asks what this character's health is.
     * @return the current health of this character.
     */
    int getHealth() const;

    /**
     * Convenience behaviour to reduce this character's health by some amount,
     * down to zero but not below zero.
     * @param theDamageAmount the amount to reduce this character's health by
     */
    void damage(int theDamageAmount);

    /**
     * Convenience behaviour to increase this character's health by some amount,
     * up to but not exceeding this character's maximum health.
     * @param theHealAmount the amount to increase this character's health by
     */
    void heal(int theHealAmount);

    /**
     * Sets the movement speed for this character.
     * @param theNewMovementSpeed the new movement speed in pixels per tick
     */
    void setMovementSpeed(int theNewMovementSpeed);

    /**
     * Sets the new maximum movement speed for this character
     * @param theNewBaseMovementSpeed the new maximum movement speed in pixels per tick
     */
    void setBaseMovementSpeed(int theNewBaseMovementSpeed);

    /**
     * Gets the movement speed for this character.
     * @return the movement speed for this character in pixels per tick
     */
    int getMovementSpeed() const;

    /**
     * Gets the base movement speed for this character.
     * @return  the base movement speed in pixels per tick
     */
    int getBaseMovementSpeed() const;

    /**
     * Sends out an attack event to the engine using this character's equipped weapon.
     */
    virtual void attack() = 0;

};



#endif //ABSTRACTCHARACTER_H
