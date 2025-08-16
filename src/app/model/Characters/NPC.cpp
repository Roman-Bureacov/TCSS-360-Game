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

void NPC::Update(Subject *theChangedSubject, const std::string &thePropertyName) {
    //TODO

}

void NPC::attackPlayer() {

    Bitz::enqueueAttackEvent(this);

}

bool NPC::canAttack() {

    int xDiff = std::abs(this->getX() - player->getX());
    int yDiff = std::abs(this->getY() - player->getY());

    return xDiff < 5 && yDiff < 5;

}

void NPC::lookAtPlayer() {

    int xDiff = this->getX() - player->getX();
    int yDiff = this->getY() - player->getY();

    if (std::abs(xDiff) > std::abs(yDiff)) {
        if  (xDiff < 0) this->setDirection(util::Direction::EAST);
        else this->setDirection(util::Direction::WEST);
    } else {
        if (yDiff < 0) this->setDirection(util::Direction::SOUTH);
        else this->setDirection(util::Direction::NORTH);
    }
}

void NPC::takeAction() {
    if (canAttack()) {
        this->lookAtPlayer();
        attackPlayer();
    } else {
        moveNPCToPlayer();
    }
}

// =========================
// Goblin
// =========================

Goblin::Goblin(
            const std::string& theName, int theMaxHealth, int theMovementSpeed)
            : NPC(theName, theMaxHealth, theMovementSpeed) {
    name = theName;
    movementSpeed = theMovementSpeed;
    maxHealth = theMaxHealth;
}

// =========================
// Skeleton
// =========================

Skeleton::Skeleton(
            const std::string& theName, int theMaxHealth, int theMovementSpeed)
            : NPC(theName, theMaxHealth, theMovementSpeed) {
    name = theName;
    movementSpeed = theMovementSpeed;
    maxHealth = theMaxHealth;
}
// =========================
// TimCapaul
// =========================

TimCapaul::TimCapaul()
    : NPC(TimCapaul::name, TimCapaul::maxHealth, TimCapaul::movementSpeed) {}

void TimCapaul::takeAction() {
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
    return std::make_shared<Goblin>(
        NPCStats::goblinName, NPCStats::goblinMaxHealth
            , NPCStats::goblinMovementSpeed);
}

//TODO: Change to be modern Implimentation.
std::shared_ptr<TimCapaul> NPC::timCapaulFactory() {
    return std::make_shared<TimCapaul>();
}

std::shared_ptr<Skeleton> NPC::skeletonFactory() {
    return std::make_shared<Skeleton>(
        NPCStats::skeletonName, NPCStats::skeletonMaxHealth
            , NPCStats::skeletonMovementSpeed);
}
