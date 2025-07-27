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
    std::string id;
    int myHealth = 0;
    int myMaxHealth = 0;
    float myMovementSpeed = 0;
public:
    /**
     * Retrieve the unique ID for this character.
     * @return the unique ID attributed to this character
     */
    std::string getID();

    /**
     * Asks if this character is alive (might need to call the reaper).
     * @return if the character is alive
     */
    bool isAlive();

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
    int getMaxHealth();

    /**
     * Sets the health for this charcter.
     * @param theNewHealth the new health for this character
     */
    void setHealth(int theNewHealth);

    /**
     * Asks what this character's health is.
     * @return the current health of this character.
     */
    int getHealth();

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
     * Sends out an attack event to the engine using this character's equipped weapon.
     */
    void attack();




};



#endif //ABSTRACTCHARACTER_H
