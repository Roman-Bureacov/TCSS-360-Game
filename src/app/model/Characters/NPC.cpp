//
// Created by riley on 8/10/25.
//

#include "../../../include/NPC.h"

NPC::NPC(const std::string& theName, int theMaxHealth, int theMovementSpeed)
    : AbstractCharacter(theName, theMaxHealth, theMovementSpeed) {

}

void NPC::moveNPCToPlayer() {
    const int xDiff = this->getX() - player->getX();
    const int yDiff = this->getY() - player->getY();

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
    //Could use this or walking animation.
    this->notify(PROPERTY_LOCATION_CHANGED);

}

void NPC::attackPlayer() {

    this->notify(PROPERTY_ATTACK);
    Bitz::enqueueAttackEvent(this);

}

bool NPC::canAttack() const {

    const int xDiff = std::abs(this->getX() - player->getX());
    const int yDiff = std::abs(this->getY() - player->getY());

    return xDiff < 5 && yDiff < 5;

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
    //Makes sure that the pointer points to something.
    if (!player) return;
    if (!active) return;

    if (canAttack()) {
        this->lookAtPlayer();
        attackPlayer();
    } else {
        moveNPCToPlayer();
    }
}

void NPC::setActive(const bool act) {
    active = act;
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
    if (this->canAttack()) {
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
    auto goblin =  std::make_shared<Goblin>();
    Bitz::enqueueAttackEvent(goblin.get());
    return goblin;
}

std::shared_ptr<TimCapaul> NPC::timCapaulFactory() {
    auto tim = std::make_shared<TimCapaul>();
    Bitz::enqueueAttackEvent(tim.get());
    return tim;
}

std::shared_ptr<Skeleton> NPC::skeletonFactory() {
    auto skeleton = std::make_shared<Skeleton>();
    Bitz::registerCharacter(skeleton.get());
    return skeleton;
}
