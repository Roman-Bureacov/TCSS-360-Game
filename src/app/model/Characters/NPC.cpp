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
    int step;

    if (xDiff == 0 && yDiff == 0) return;



    if (std::abs(xDiff) > std::abs(yDiff)) {
        if  (xDiff < 0) {
            this->setDirection(util::Direction::EAST);
        }else {
            this->setDirection(util::Direction::WEST);
        }
        step = std::min(std::abs(xDiff), this->getMovementSpeed());

    } else {
        if (yDiff > 0) {
            this->setDirection(util::Direction::SOUTH);
        } else {
            this->setDirection(util::Direction::NORTH);
        }
        step = std::min(std::abs(yDiff), this->getMovementSpeed());
    }
    Bitz::enqueueMovementEvent(this, step);


}

void NPC::Update(Subject *theChangedSubject, const std::string &thePropertyName) {
    //TODO

}

void NPC::attackPlayer() {
    notify(PROPERTY_KILLED);

    Bitz::enqueueAttackEvent(this);
}

bool NPC::canAttack() {

    const int xDiff = std::abs(this->getX() - player->getX());
    const int yDiff = std::abs(this->getY() - player->getY());

    return xDiff < 50 && yDiff < 50;

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

    if (xDiff == 0 && yDiff == 0) return;

    if (std::abs(xDiff) > std::abs(yDiff)) {
        if  (xDiff < 0) this->setDirection(util::Direction::EAST);
        else this->setDirection(util::Direction::WEST);
    } else {
        if (yDiff > 0) this->setDirection(util::Direction::SOUTH);
        else this->setDirection(util::Direction::NORTH);
    }
}

void NPC::takeAction() {

    if (!active) return;

    //Kills the NPC
    if (!isAlive()) {
        setIsActive(false);
        return;
    }
    if (canAttack()) {
        lookAtPlayer();
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
    Weapon* npcWeapon =
        new Weapon(1, 10, std::move(NPCWeaponHitbox));
    this->giveWeapon(npcWeapon);
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
    Weapon* npcWeapon =
        new Weapon(10, 10, std::move(NPCWeaponHitbox));
    this->giveWeapon(npcWeapon);
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
