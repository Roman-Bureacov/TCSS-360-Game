//
// Created by riley on 7/23/25.
//

#ifndef ABSTRACTCHARACTER_H
#define ABSTRACTCHARACTER_H
#include <string>

#include "Hitbox.h"
#include "ObserverPattern.h"
#include "../app/model/Characters/Weapons/Weapon.h"


/**
 * Represents the basic character.
 * @author Riley Hopper
 * @author Roman Bureacov
 * @version 2025 July
 */
class AbstractCharacter : public Subject, public Observer {
private:
    const std::string myName;
    const long long myID;
    int myHealth = 0;
    int myMaxHealth = 0;
    int myBaseMovement = 0;
    int myCurrentMovement = 0;
    util::Point myOrigin;
    Hitbox myHitbox;
    Weapon* myWeapon;
    util::Direction myDirection;
public:
    /** the property name for when the character is damaged. */
    inline static const std::string PROPERTY_DAMAGED = "I have been damaged!";
    /** the property name for when the character is healed. */
    inline static const std::string PROPERTY_HEALED = "I have been healed!";
    /** the property name for when the character's health changed. */
    inline static const std::string PROPERTY_HEALTH_CHANGED = "My health changed!";
    /** the property name for when the character's max health changed. */
    inline static const std::string PROPERTY_MAX_HEALTH_CHANGED = "My Max health changed!";
    /** the property name for when the character's weapon changed. */
    inline static const std::string PROPERTY_WEAPON_CHANGED = "My weapon changed!";
    /** the property name for when the character's movement speed changed. */
    inline static const std::string PROPERTY_MVMT_CHANGED = "My movement speed changed!";
    /** the property name for when the character's base movement speed changed. */
    inline static const std::string PROPERTY_BASE_MVMT_CHANGED = "My base movement speed changed!";
    /** the property name for when the character's location changed. */
    inline static const std::string PROPERTY_LOCATION_CHANGED = "My location changed!";
    /** the property name for when the character's health reached zero. */
    inline static const std::string PROPERTY_KILLED = "I have been slain!";
    /** the property name for when the character's hitbox changed. */
    inline static const std::string PROPERTY_HITBOX_CHANGED = "My hitbox changed!";
    /** the property name for when the character's direction changed. */
    inline static const std::string PROPERTY_DIRECTION_CHANGED = "My direction changed!";

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
    long long getID() const;

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
     * @return the base movement speed in pixels per tick
     */
    int getBaseMovementSpeed() const;

    /**
     * Gets the X position for this character.
     * @return the X position in pixels
     */
    int getX() const;

    /**
     * Gets the Y position for this character.
     * @return the Y position in pixels
     */
    int getY() const;

    /**
     * Sets the X position of this character.
     * @param theNewX the new X position in pixels
     */
    void setX(int theNewX);

    /**
     * Sets the Y position of this character.
     * @param theNewY the new Y position in pixels
     */
    void setY(int theNewY);

    /**
     * Gets the hitbox for this character.
     * @return the immutable hitbox for this character
     */
    const Hitbox& getHitbox() const;

    /**
     * Sets the hitbox for this character.
     * @param theNewHitbox the new hitbox for this character
     */
    void setHitbox(Hitbox& theNewHitbox);

    /**
     * Convenience behavior to set the hitbox for this character using explicit parameters.
     * @param theWidth the width in pixels for the new hitbox
     * @param theHeight the height in pixels for the new hitbox
     */
    void setHitbox(int theWidth, int theHeight);

    /**
     * Gets the weapon of this character.
     * @return the weapon this character is wielding
     */
    Weapon& getWeapon() const;

    /**
     * Gives this character a new weapon to equip.
     * @param theWeapon the new weapon this character will wield
     */
    void giveWeapon(Weapon* theWeapon);

    /**
     * Gets the direction this character is facing.
     * @return the direction this character is facing
     */
    util::Direction getDirection() const;

    /**
     * Sets the direction for this character.
     * @param theDirection the new direction for this character
     */
    void setDirection(util::Direction theDirection);

    /**
     * Gets the attack hitbox for attack events.
     * @return the appropriate hitbox based on the weapon of this character,
     * centered at the respective direction of this character.
     */
    const Hitbox& getAttackHitbox() const;

};



#endif //ABSTRACTCHARACTER_H
