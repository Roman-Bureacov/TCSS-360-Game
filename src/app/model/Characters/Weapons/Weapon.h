//
// Created by iwant on 8/3/2025.
//

#ifndef WEAPON_H
#define WEAPON_H
#include "../../../../include/Hitbox.h"

/**
 * Struct that represents a basic weapon.
 * @author Roman Bureacov
 * @version August 2025
 */
struct Weapon {
    const int attackTicks;
    const int damage;
    Hitbox& hitboxNorth;
    Hitbox& hitboxEast;
    Hitbox& hitboxSouth;
    Hitbox& hitboxWest;
    float damageMultiplier = 1;

    /**
     * Creates a weapon.
     * @param theDamage the damage this weapon will do
     * @param theAttackTicks the number of ticks this weapon lasts
     * @param theHitboxNorth the hitbox when attacking north
     * @param theHitboxEast the hitbox when attacking east
     * @param theHitboxSouth the hitbox when attacking south
     * @param theHitboxWest the hitbox when attacking west
     */
    Weapon(
        const int theAttackTicks,
        const int theDamage,
        Hitbox& theHitboxNorth,
        Hitbox& theHitboxEast,
        Hitbox& theHitboxSouth,
        Hitbox& theHitboxWest
    ) : attackTicks(theAttackTicks),
        damage(theDamage),
        hitboxNorth(theHitboxNorth),
        hitboxEast(theHitboxEast),
        hitboxSouth(theHitboxSouth),
        hitboxWest(theHitboxWest) {

    }

    /**
     * Creates a weapon with the same hitbox in the north-south and east-west directions.
     * @param theDamage the damage this weapon will do
     * @param theAttackTicks the number of ticks this weapon lasts
     * @param theHitboxNorthSouth the hitbox when attacking north or south
     * @param theHitboxEastWest the hitbox when attacking east or west
     */
    Weapon(
        const int theDamage,
        const int theAttackTicks,
        Hitbox&& theHitboxNorthSouth,
        Hitbox&& theHitboxEastWest
    ) : Weapon(
        theDamage,
        theAttackTicks,
        theHitboxNorthSouth,
        theHitboxEastWest,
        theHitboxNorthSouth,
        theHitboxEastWest
        ) { }

    /**
     * Creates a weapon with the same hitbox in all directions.
     * @param theDamage the damage this weapon will do
     * @param theAttackTicks the number of ticks this weapon lasts
     * @param theHitbox the hitbox when attacking in any direction
     */
    Weapon(
        const int theDamage,
        const int theAttackTicks,
        Hitbox&& theHitbox
    ) : Weapon(
        theDamage,
        theAttackTicks,
        theHitbox,
        theHitbox,
        theHitbox,
        theHitbox
        ) { }

    /**
     * Convenience behavior to return the damage with the multiplier.
     * @return the product of the damage and the multiplier
     */
    int getModifiedDamage() const {
        return damage * damageMultiplier;
    }

};

#endif //WEAPON_H
