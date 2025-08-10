//
// Created by riley on 8/10/25.
//

#include "../../../include/NPC.h"

NPC::NPC(const std::string& theName, int theMaxHealth, int theMovementSpeed)
    : AbstractCharacter(theName, theMaxHealth, theMovementSpeed) {

}

void NPC::moveNPCToPlayer() {
    int xDiff = this->getX() - player->getX();
    int yDiff = this->getY() - player->getY();

    if (std::abs(xDiff) > std::abs(yDiff)) {
        if  (xDiff < 0) {
            this->setDirection(util::Direction::EAST);
            this->setX(this->getX() + this->getMovementSpeed());
            this->notify(PROPERTY_DIRECTION_CHANGED);
        }else {
            this->setDirection(util::Direction::WEST);
            this->setX(this->getX() - this->getMovementSpeed());
            this->notify(PROPERTY_DIRECTION_CHANGED);
        }
    } else {
        if (yDiff < 0) {
            this->setDirection(util::Direction::SOUTH);
            this->setY(this->getY() + this->getMovementSpeed());
            this->notify(PROPERTY_DIRECTION_CHANGED);
        } else {
            this->setDirection(util::Direction::NORTH);
            this->setY(this->getY() - this->getMovementSpeed());
            this->notify(PROPERTY_DIRECTION_CHANGED);
        }
    }
    this->notify(PROPERTY_LOCATION_CHANGED);

}

void NPC::attackPlayer() {

}

bool NPC::canAttack() {

    int xDiff = std::abs(this->getX() - player->getX());
    int yDiff = std::abs(this->getY() - player->getY());

    return xDiff < 5 && yDiff < 5;

}

void NPC::takeAction() {
    if (canAttack()) {
        attackPlayer();
    } else {
        moveNPCToPlayer();
    }
}

// =========================
// Goblin
// =========================

Goblin::Goblin()
    : NPC(name, maxHealth, movementSpeed) {}

// =========================
// Skeleton
// =========================

Skeleton::Skeleton()
    : NPC(name, maxHealth, movementSpeed) {}

// =========================
// TimCapaul
// =========================

TimCapaul::TimCapaul()
    : NPC(name, maxHealth, movementSpeed) {}

void TimCapaul::takeAction() {
    // TimCapaul might have more advanced behavior
    if (canAttack()) {
        attackPlayer();
    } else {
        moveNPCToPlayer();
    }
}

void TimCapaul::moveNPCToPlayer() {
}

void TimCapaul::attackPlayer() {
}

bool TimCapaul::canAttack() {
    return true;
}

// =========================
// Factory Implementations
// =========================

std::shared_ptr<Goblin> NPC::goblinFactory() {
    return std::make_shared<Goblin>();
}

std::shared_ptr<TimCapaul> NPC::timCapaulFactory() {
    return std::make_shared<TimCapaul>();
}

std::shared_ptr<Skeleton> NPC::skeletonFactory() {
    return std::make_shared<Skeleton>();
}
