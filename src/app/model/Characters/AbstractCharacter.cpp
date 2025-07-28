//
// Created by riley on 7/23/25.
//

#include "../../../include/AbstractCharacter.h"

const std::string & AbstractCharacter::getID() const {
    return nullptr;
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
