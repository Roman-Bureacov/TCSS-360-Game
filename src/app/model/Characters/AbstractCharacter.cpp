//
// Created by riley on 7/23/25.
//

#include "../../../include/AbstractCharacter.h"

#include <iostream>

AbstractCharacter::AbstractCharacter(const std::string theName, const int theMaxHealth, const float theMovementSpeed)
        : myName(theName), myID(2), myMaxHealth(theMaxHealth),
        myBaseMovement(theMovementSpeed) {
    myHealth = myMaxHealth;
}

const std::string& AbstractCharacter::getName() const {
    return myName;
}

unsigned int AbstractCharacter::getID() const {
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
