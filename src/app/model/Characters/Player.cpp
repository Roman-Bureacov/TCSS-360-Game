//
// Created by riley on 8/17/25.
//

#include "../../../include/Player.h"






std::shared_ptr<Player> Player::myInstance = nullptr;

std::shared_ptr<Player> Player::playerInstance() {

    if (!myInstance) {
        myInstance = std::shared_ptr<Player>(new Player(MYNAME,
            MYSTARTINGHEALTH, MYMOVEMENTSPEED));
    }


    return myInstance;
}

Player::Player(const std::string &theName
        , int theMaxHealth, int theMovementSpeed)
            : AbstractCharacter(theName, theMaxHealth, theMovementSpeed) {


    setHitbox(MYHITBOXSIZE, MYHITBOXSIZE);
    Weapon* PlayerWeapon =
        new Weapon(PlayerClasses::MYDAMAGEKNIGHT,
            PlayerClasses::MYPLAYERATTACKTIME, std::move(PlayerWeaponHitbox));
    this->giveWeapon(PlayerWeapon);
}

void Player::Update(Subject *theChangedSubject
        , const std::string &thePropertyName) {}

void Player::setClass(const playerTypes myType) {
    switch (myType) {
        case playerTypes::Knight:
            this->setName(PlayerClasses::MYNAMEKNIGHT);
            this->setHealth(PlayerClasses::MYSTARTINGHEALTHKNIGHT);
            this->setMovementSpeed(PlayerClasses::MYMOVEMENTSPEEDKNIGHT);
            this->giveWeapon( new Weapon(PlayerClasses::MYDAMAGEKNIGHT,
            PlayerClasses::MYPLAYERATTACKTIME, std::move(PlayerWeaponHitbox)));
            break;

        case playerTypes::Rogue:
            this->setName(PlayerClasses::MYNAMEROGUE);
            this->setHealth(PlayerClasses::MYSTARTINGHEALTHROGUE);
            this->setMovementSpeed(PlayerClasses::MYMOVEMENTSPEEDROGUE);
            this->giveWeapon( new Weapon(PlayerClasses::MYDAMAGEROGUE,
            PlayerClasses::MYPLAYERATTACKTIME, std::move(PlayerWeaponHitbox)));
            break;

        case playerTypes::Mage:
            this->setName(PlayerClasses::MYNAMEMAGE);
            this->setHealth(PlayerClasses::MYSTARTINGHEALTHMAGE);
            this->setMovementSpeed(PlayerClasses::MYMOVEMENTSPEEDMAGE);
            this->giveWeapon( new Weapon(PlayerClasses::MYDAMAGEMAGE,
            PlayerClasses::MYPLAYERATTACKTIME, std::move(PlayerWeaponHitbox)));
            break;

        case playerTypes::Archer:
            this->setName(PlayerClasses::MYNAMEARCHER);
            this->setHealth(PlayerClasses::MYSTARTINGHEALTHARCHER);
            this->setMovementSpeed(PlayerClasses::MYMOVEMENTSPEEDARCHER);
            this->giveWeapon( new Weapon(PlayerClasses::MYDAMAGEARCHER,
            PlayerClasses::MYPLAYERATTACKTIME, std::move(PlayerWeaponHitbox)));
            break;

        default:
            // Fallback to Knight if type is unrecognized
            this->setName(PlayerClasses::MYNAMEKNIGHT);
            this->setHealth(PlayerClasses::MYSTARTINGHEALTHKNIGHT);
            this->setMovementSpeed(PlayerClasses::MYMOVEMENTSPEEDKNIGHT);
            this->giveWeapon( new Weapon(PlayerClasses::MYDAMAGEKNIGHT,
            PlayerClasses::MYPLAYERATTACKTIME, std::move(PlayerWeaponHitbox)));
            break;
    }
    this->notify(PROPERTY_CHANGE_CLASS);

}

void Player::userInput(const int theCode) {
    if (!isAlive()) return;
    switch (theCode) {
        case SDL_SCANCODE_W:
            setDirection(util::SOUTH);
            std::cout << "w";
            Bitz::enqueueMovementEvent(this,MYMOVEMENTSPEED);
            break;
        case SDL_SCANCODE_S:
            setDirection(util::NORTH);
            std::cout << "s";
            Bitz::enqueueMovementEvent(this,MYMOVEMENTSPEED);
            break;
        case SDL_SCANCODE_A:
            setDirection(util::WEST);
            std::cout << "a";
            Bitz::enqueueMovementEvent(this,MYMOVEMENTSPEED);
            break;
        case SDL_SCANCODE_D:
            setDirection(util::EAST);
            std::cout << "d";
            Bitz::enqueueMovementEvent(this,MYMOVEMENTSPEED);
            break;
        case SDL_SCANCODE_SPACE:
            attack();
            break;
        case SDL_SCANCODE_RIGHT:
            Bitz::loadDungeonRoom(util::EAST);
            break;
        case SDL_SCANCODE_LEFT:
            Bitz::loadDungeonRoom(util::WEST);
            break;
        case SDL_SCANCODE_DOWN:
            Bitz::loadDungeonRoom(util::SOUTH);
            break;
        case SDL_SCANCODE_UP:
            Bitz::loadDungeonRoom(util::NORTH);
            break;
        case SDL_SCANCODE_LSHIFT:
            usePotion();
            break;
        default: break;
        }
    }

//Just isn't setup in engine
void Player::roll() {
    switch (getDirection()) {
        case util::NORTH:
            Bitz::enqueueMovementEvent(this, ROLLDISPLACEMENT);
        break;
        case util::EAST:
            Bitz::enqueueMovementEvent(this, ROLLDISPLACEMENT);
        break;
        case util::SOUTH:
            Bitz::enqueueMovementEvent(this, ROLLDISPLACEMENT);
        break;
        case util::WEST:
            Bitz::enqueueMovementEvent(this, ROLLDISPLACEMENT);
        break;
        default:
            throw new std::logic_error("Unknown direction enum");
    }

    //So where this needs to become false again.
    myRolling = true;

}

bool Player::isRolling() {
    return myRolling;
}

void Player::endRoll() {
    myRolling = false;
}

void Player::usePotion() {
    if (myPotionAmount > 0) {
        myPotionAmount--;
        heal(MYPOTIONSTRENGTH);
    }
}

void Player::givePotion() {
    std::cout << "You've got a new potion" << std::endl;
    myPotionAmount++;
}

int Player::getPotionAmount() {
    return myPotionAmount;
}

void Player::setPotionAmount(const int theAmount) {
    //You can't have a negative amount
    if (theAmount >= 0) {
        myPotionAmount = theAmount;
    }

}

void Player::attack() {
    if (myInstance) {
        Bitz::enqueueAttackEvent(myInstance.get());
    }

}

int Player::getHitBoxSize() {
    return MYHITBOXSIZE;
}


