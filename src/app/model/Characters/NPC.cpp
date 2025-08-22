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

    Bitz::enqueueAttackEvent(this);
}

bool NPC::canAttack() const {

    const int xDiff = std::abs(this->getX() - player->getX());
    const int yDiff = std::abs(this->getY() - player->getY());

    return xDiff <= 100 && yDiff <= 100;

}

void NPC::setIsActive(const bool isActive) {
    active = isActive;
    notify(PROPERTY_ACTIVE_CHANGED);
}

bool NPC::getIsActive() const {
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
            const std::string& theName, const int theMaxHealth, const int theMovementSpeed)
            : NPC(theName, theMaxHealth, theMovementSpeed) {
    Weapon* npcWeapon =
        new Weapon(NPCStats::MYGOBLINDAMAGE,
            NPCStats::MYNPCATTACKTIME, std::move(myNPCWeaponHitbox));
    this->giveWeapon(npcWeapon);
    this->setHitbox(myNPCHitBox);
    myName = theName;
    myMovementSpeed = theMovementSpeed;
    myMaxHealth = theMaxHealth;
}

// =========================
// Skeleton
// =========================

Skeleton::Skeleton(
            const std::string& theName, int theMaxHealth, int theMovementSpeed)
            : NPC(theName, theMaxHealth, theMovementSpeed) {
    const auto npcWeapon =
        new Weapon(NPCStats::MYSKELETONDAMAGE,
            NPCStats::MYNPCATTACKTIME, std::move(myNPCWeaponHitbox));
    this->giveWeapon(npcWeapon);
    this->setHitbox(myNPCHitBox);
    myName = theName;
    myMovementSpeed = theMovementSpeed;
    myMaxHealth = theMaxHealth;
}
// =========================
// TimCapaul
// =========================

TimCapaul::TimCapaul( const std::string& theName, const int theMaxHealth, const int theMovementSpeed)
            : NPC(theName, theMaxHealth, theMovementSpeed) {
    const auto npcWeapon =
       new Weapon(NPCStats::MYBOSSDAMAGE,
           NPCStats::MYNPCATTACKTIME, std::move(myNPCWeaponHitbox));
    this->giveWeapon(npcWeapon);
    this->setHitbox(myNPCHitBox);
    myName = theName;
    myMovementSpeed = theMovementSpeed;
    myMaxHealth = theMaxHealth;

}


// =========================
// Factory Implementations
// =========================

std::shared_ptr<Goblin> NPC::goblinFactory() {
    auto goblin = std::make_shared<Goblin>(
        NPCStats::MYGOBLINNAME,
        NPCStats::MYGOBLINMAXHEALTH,
        NPCStats::MYGOBLINMOVEMENTSPEED
    );

    //Should randomize spawn position.
    setRandomPosition(goblin);
    return goblin;

}

std::shared_ptr<TimCapaul> NPC::timCapaulFactory() {
    auto tim = std::make_shared<TimCapaul>(
        NPCStats::MYBOSSNAME,
        NPCStats::MYBOSSMAXHEALTH,
        NPCStats::MYBOSSMOVEMENTSPEED
    );
    setRandomPosition(tim);
    return tim;
}

std::shared_ptr<Skeleton> NPC::skeletonFactory() {
    auto skeleton = std::make_shared<Skeleton>(
        NPCStats::MYSKELETONNAME,
        NPCStats::MYSKELETONMAXHEALTH,
        NPCStats::MYSKELETONMOVEMENTSPEED
    );
    setRandomPosition(skeleton);
    return skeleton;
}
