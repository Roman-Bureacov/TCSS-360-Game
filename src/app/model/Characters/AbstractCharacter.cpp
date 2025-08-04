//
// Created by riley on 7/23/25.
//

#include "../../../include/AbstractCharacter.h"

#include <iostream>

#include "../ID_GEN.h"

AbstractCharacter::AbstractCharacter(
    const std::string& theName,
    const int theMaxHealth,
    const int theMovementSpeed)
    : myName(theName),
      myID(ID_GEN::makeID()),
      myHealth(theMaxHealth),
      myMaxHealth(theMaxHealth),
      myBaseMovement(theMovementSpeed),
      myCurrentMovement(theMovementSpeed),
      myHitbox(Hitbox(util::Point(), 100, 100)),
      myDirection(util::NORTH) {

    myWeapon = nullptr;
}

const std::string& AbstractCharacter::getName() const {
    return myName;
}

long long AbstractCharacter::getID() const {
    return myID;
}

bool AbstractCharacter::isAlive() const {
    return myHealth > 0;
}

void AbstractCharacter::setMaxHealth(const int theNewMaxHealth) {
    myHealth = theNewMaxHealth;
}

int AbstractCharacter::getMaxHealth() const {
    return myMaxHealth;
}

void AbstractCharacter::setHealth(const int theNewHealth) {
    myHealth = theNewHealth;
}

int AbstractCharacter::getHealth() const {
    return myHealth;
}

void AbstractCharacter::damage(const int theDamageAmount) {
    if (myHealth > theDamageAmount) myHealth -= theDamageAmount;
    else myHealth = 0;
}

void AbstractCharacter::heal(const int theHealAmount) {
    myHealth += theHealAmount;
    if (myHealth > myMaxHealth) myHealth = myMaxHealth;
}

void AbstractCharacter::setMovementSpeed(const int theNewMovementSpeed) {
    myCurrentMovement = theNewMovementSpeed;
}

void AbstractCharacter::setBaseMovementSpeed(const int theNewBaseMovementSpeed) {
    myBaseMovement = theNewBaseMovementSpeed;
}

int AbstractCharacter::getMovementSpeed() const {
    return myCurrentMovement;
}

int AbstractCharacter::getBaseMovementSpeed() const {
    return myBaseMovement;
}

int AbstractCharacter::getX() const {
    return myOrigin.x;
}

int AbstractCharacter::getY() const {
    return myOrigin.y;
}

void AbstractCharacter::setX(const int theNewX) {
    myHitbox.setOrigin(theNewX, myOrigin.y);
    myOrigin.x = theNewX;
}

void AbstractCharacter::setY(const int theNewY) {
    myHitbox.setOrigin(myOrigin.x, theNewY);
    myOrigin.y = theNewY;
}

const Hitbox& AbstractCharacter::getHitbox() const {
    return myHitbox;
}

void AbstractCharacter::setHitbox(Hitbox& theNewHitbox) {
    theNewHitbox.setOrigin(myOrigin);
    myHitbox = theNewHitbox;
}

void AbstractCharacter::setHitbox(const int theWidth, const int theHeight) {
    myHitbox = Hitbox(myOrigin, theWidth, theHeight);
}

Weapon& AbstractCharacter::getWeapon() const {
    return *myWeapon;
}

void AbstractCharacter::giveWeapon(Weapon* theWeapon) {
    if (myWeapon) delete myWeapon;
    myWeapon = theWeapon;
}

util::Direction AbstractCharacter::getDirection() const {
    return myDirection;
}

void AbstractCharacter::setDirection(const util::Direction theDirection) {
    myDirection = theDirection;
}

const Hitbox& AbstractCharacter::getAttackHitbox() const {

    Hitbox* h;
    int xOffset;
    int yOffset;

    // TODO: need to redefine how this hitbox is gathered
    // myDimension - (myDimension + weapDimension)/2
    switch (myDirection) {
        case util::NORTH:
            h = &myWeapon->hitboxNorth;
            xOffset = myHitbox.getWidth() / 4;
            yOffset = myHitbox.getHeight();
            break;
        case util::EAST:
            h = &myWeapon->hitboxEast;
            xOffset = myHitbox.getWidth();
            yOffset = myHitbox.getHeight() / 4;
            break;
        case util::SOUTH:
            h = &myWeapon->hitboxSouth;
            xOffset = myHitbox.getWidth() / 4;
            yOffset = -myHitbox.getHeight();
            break;
        case util::WEST:
            h = &myWeapon->hitboxWest;
            xOffset = -myHitbox.getWidth();
            yOffset = myHitbox.getHeight() / 4;
            break;
        default: throw new std::logic_error("Bad direction in getAttackHitbox");
    }

    h->setOrigin(
            getX() + xOffset,
            getY() + yOffset
        );

    return *h;

}
