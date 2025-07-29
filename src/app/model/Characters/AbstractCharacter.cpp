//
// Created by riley on 7/23/25.
//

#include "../../../include/AbstractCharacter.h"

#include <iostream>

AbstractCharacter::AbstractCharacter(const std::string theName, const int theMaxHealth, const float theMovementSpeed)
        : myName(theName), myID(2), myMaxHealth(theMaxHealth),
        myMovementSpeed(theMovementSpeed) {
    myHealth = myMaxHealth;
}



const std::string& AbstractCharacter::getName() const {
    return myName;
}

unsigned int AbstractCharacter::getID() const {
    return myID;
}

bool AbstractCharacter::isAlive() const {
    return false;
}

void AbstractCharacter::setMaxHealth(int theNewMaxHealth) {
}

int AbstractCharacter::getMaxHealth() const {
    return 0;
}

void AbstractCharacter::setHealth(int theNewHealth) {
}

int AbstractCharacter::getHealth() const {
    return 0;
}

void AbstractCharacter::damage(int theDamageAmount) {
}

void AbstractCharacter::heal(int theHealAmount) {
}

void AbstractCharacter::attack() {
}
