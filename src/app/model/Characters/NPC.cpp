//
// Created by riley on 8/10/25.
//

#include <utility>

#include "../../../include/NPC.h"

NPC::NPC(const std::string& theName, int theMaxHealth, int theMovementSpeed)
    : AbstractCharacter(theName, theMaxHealth, theMovementSpeed) {

}

void NPC::setPlayer(std::shared_ptr<AbstractCharacter> thePlayer) {
    player = std::move(thePlayer);
}

void NPC::moveNPCToPlayer() {
    const int xDiff = this->getX() - player->getX();
    const int yDiff = this->getY() - player->getY();

    if (std::abs(xDiff) > std::abs(yDiff)) {
        if  (xDiff < 0) {
            this->setDirection(util::Direction::EAST);
            Bitz::enqueueMovementEvent(this,this->getMovementSpeed());
        }else {
            this->setDirection(util::Direction::WEST);
            Bitz::enqueueMovementEvent(this, -this->getMovementSpeed());
        }
    } else {
        if (yDiff < 0) {
            this->setDirection(util::Direction::SOUTH);
            Bitz::enqueueMovementEvent(this,this->getMovementSpeed());
        } else {
            this->setDirection(util::Direction::NORTH);
            Bitz::enqueueMovementEvent(this, -this->getMovementSpeed());

        }
    }
}

void NPC::Update(Subject *theChangedSubject, const std::string &thePropertyName) {
    //TODO

}

void NPC::attackPlayer() {

    Bitz::enqueueAttackEvent(this);

}

bool NPC::canAttack() {

    const int xDiff = std::abs(this->getX() - player->getX());
    const int yDiff = std::abs(this->getY() - player->getY());

    return xDiff < 5 && yDiff < 5;

}

void NPC::setIsActive(const bool isActive) {
    active = isActive;
    notify(PROPERTY_ACTIVE_CHANGED);
}

bool NPC::getIsActive() {
    return active;
}

void NPC::lookAtPlayer() {

    const int xDiff = this->getX() - player->getX();
    const int yDiff = this->getY() - player->getY();

    if (std::abs(xDiff) > std::abs(yDiff)) {
        if  (xDiff < 0) this->setDirection(util::Direction::EAST);
        else this->setDirection(util::Direction::WEST);
    } else {
        if (yDiff < 0) this->setDirection(util::Direction::SOUTH);
        else this->setDirection(util::Direction::NORTH);
    }
}

void NPC::takeAction() {

    //If the NPC isn't active it will take no actions.
    if (!active) return;

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
//TODO


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
    auto goblin = std::make_shared<Goblin>(
        NPCStats::goblinName,
        NPCStats::goblinMaxHealth,
        NPCStats::goblinMovementSpeed
    );

    //Should randomize spawn position.
    setRandomPosition(goblin);
    return goblin;

}

//TODO: Change to be modern Implimentation.
std::shared_ptr<TimCapaul> NPC::timCapaulFactory() {
    return std::make_shared<TimCapaul>();
}

std::shared_ptr<Skeleton> NPC::skeletonFactory() {
    auto skeleton = std::make_shared<Skeleton>(
        NPCStats::skeletonName,
        NPCStats::skeletonMaxHealth,
        NPCStats::skeletonMovementSpeed
    );
    setRandomPosition(skeleton);
    return skeleton;
}
