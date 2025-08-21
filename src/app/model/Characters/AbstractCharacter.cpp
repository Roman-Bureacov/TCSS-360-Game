//
// Created by riley on 7/23/25.
//

#include "../../../include/AbstractCharacter.h"

#include <iostream>

#include "../../../include/ID_GEN.h"

AbstractCharacter::AbstractCharacter(
    const std::string& theName,
    const int theMaxHealth,
    const int theMovementSpeed)
    : myName(theName),
      MYID(ID_GEN::makeID()),
      myHealth(theMaxHealth),
      myMaxHealth(theMaxHealth),
      myBaseMovement(theMovementSpeed),
      myCurrentMovement(theMovementSpeed),
      myHitbox(Hitbox(util::Point(), 100, 100)),
      myDirection(util::NORTH),
      myInteractionHitbox(100, 100) {

    myWeapon = nullptr;
}

const std::string& AbstractCharacter::getName() const {
    //std::cout << "retrieving name..." << std::endl;
    return myName;
}

long long AbstractCharacter::getID() const {
    return MYID;
}

bool AbstractCharacter::isAlive() const {
    return myHealth > 0;
}

void AbstractCharacter::setMaxHealth(const int theNewMaxHealth) {
    myHealth = theNewMaxHealth;
    notify(PROPERTY_MAX_HEALTH_CHANGED);
}

int AbstractCharacter::getMaxHealth() const {
    return myMaxHealth;
}

void AbstractCharacter::setHealth(const int theNewHealth) {
    myHealth = theNewHealth;
    if (myHealth == 0) notify(PROPERTY_KILLED);
    else notify(PROPERTY_HEALTH_CHANGED);
}

int AbstractCharacter::getHealth() const {
    return myHealth;
}

void AbstractCharacter::damage(const int theDamageAmount) {
    if (myHealth > theDamageAmount) {
        myHealth -= theDamageAmount;
        notify(PROPERTY_DAMAGED);
    } else {
        myHealth = 0;
        notify(PROPERTY_KILLED);
    }
}

void AbstractCharacter::heal(const int theHealAmount) {
    myHealth += theHealAmount;
    if (myHealth > myMaxHealth) myHealth = myMaxHealth;
    notify(PROPERTY_HEALED);
}

void AbstractCharacter::setMovementSpeed(const int theNewMovementSpeed) {
    myCurrentMovement = theNewMovementSpeed;
    notify(PROPERTY_MVMT_CHANGED);
}

void AbstractCharacter::setBaseMovementSpeed(const int theNewBaseMovementSpeed) {
    myBaseMovement = theNewBaseMovementSpeed;
    notify(PROPERTY_BASE_MVMT_CHANGED);
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
    notify(PROPERTY_LOCATION_CHANGED);
}

void AbstractCharacter::setY(const int theNewY) {
    myHitbox.setOrigin(myOrigin.x, theNewY);
    myOrigin.y = theNewY;
    notify(PROPERTY_LOCATION_CHANGED);
}

const Hitbox& AbstractCharacter::getHitbox() const {
    return myHitbox;
}

void AbstractCharacter::setHitbox(Hitbox& theNewHitbox) {
    theNewHitbox.setOrigin(myOrigin);
    myHitbox = theNewHitbox;
    notify(PROPERTY_HITBOX_CHANGED);
}

void AbstractCharacter::setHitbox(const int theWidth, const int theHeight) {
    myHitbox = Hitbox(myOrigin, theWidth, theHeight);
    notify(PROPERTY_HITBOX_CHANGED);
}

Weapon& AbstractCharacter::getWeapon() const {
    return *myWeapon;
}

void AbstractCharacter::giveWeapon(Weapon* theWeapon) {
    if (myWeapon) delete myWeapon;
    myWeapon = theWeapon;
    notify(PROPERTY_WEAPON_CHANGED);
}

util::Direction AbstractCharacter::getDirection() const {
    return myDirection;
}

void AbstractCharacter::setDirection(const util::Direction theDirection) {
    myDirection = theDirection;
    notify(PROPERTY_DIRECTION_CHANGED);
}

const Hitbox& AbstractCharacter::getAttackHitbox() const {

        Hitbox* hb;

        // myDimension - (myDimension + weapDimension)/2
        // simplified to (myDimension - weapDimension)/2
        switch (myDirection) {
            case util::NORTH:
                hb = &myWeapon->hitboxNorth;
                myHitbox.project(*hb, util::NORTH);
                break;
            case util::EAST:
                hb = &myWeapon->hitboxEast;
                myHitbox.project(*hb, util::EAST);
                break;
            case util::SOUTH:
                hb = &myWeapon->hitboxSouth;
                myHitbox.project(*hb, util::SOUTH);
                break;
            case util::WEST:
                hb = &myWeapon->hitboxWest;
                myHitbox.project(*hb, util::WEST);
                break;
            default: throw new std::logic_error("Bad direction in getAttackHitbox");
        }

        return *hb;

}

void AbstractCharacter::setInteractionHitbox(const int theWidth, const int theHeight) {
    myInteractionHitbox = Hitbox(theWidth, theHeight);
}

void AbstractCharacter::setRandomPosition(const std::shared_ptr<AbstractCharacter> &character) {

    static std::random_device rd;
    static std::mt19937 gen(rd());

    //This should set a random position within in the dungeon.
    std::uniform_int_distribution<> xDist(Room::TILESIZE * 3
        , (Room::ROOMSIZE * Room::TILESIZE)- (Room::TILESIZE * 3));
    std::uniform_int_distribution<> yDist(Room::TILESIZE * 3
        , (Room::ROOMSIZE * Room::TILESIZE)- (Room::TILESIZE * 3));

    character->setX(xDist(gen));
    character->setY(yDist(gen));

}

void AbstractCharacter::setName(std::string theName) {
    this->myName = theName;
}

const Hitbox& AbstractCharacter::getInteractionHitbox() const {
    myHitbox.project(myInteractionHitbox, myDirection);
    return myInteractionHitbox;
}

