//
// Created by riley on 8/17/25.
//

#include "../../../include/Player.h"






std::shared_ptr<Player> Player::instance = nullptr;

std::shared_ptr<Player> Player::playerInstance() {

    if (!instance) {
        instance = std::shared_ptr<Player>(new Player(name,
            startingHealth, movementSpeed));
    }


    return instance;
}

Player::Player(const std::string &theName
        , int theMaxHealth, int theMovementSpeed)
            : AbstractCharacter(theName, theMaxHealth, theMovementSpeed) {


    setHitbox(hitBoxSize, hitBoxSize);
    Weapon* PlayerWeapon =
        new Weapon(10, 10, std::move(PlayerWeaponHitbox));
    this->giveWeapon(PlayerWeapon);
}

void Player::Update(Subject *theChangedSubject
        , const std::string &thePropertyName) {}

void Player::userInput(int code) {
    if (!isAlive()) return;
    switch (code) {
        case SDL_SCANCODE_W:
            setDirection(util::SOUTH);
            std::cout << "w";
            Bitz::enqueueMovementEvent(this,movementSpeed);
            break;
        case SDL_SCANCODE_S:
            setDirection(util::NORTH);
            std::cout << "s";
            Bitz::enqueueMovementEvent(this,movementSpeed);
            break;
        case SDL_SCANCODE_A:
            setDirection(util::WEST);
            std::cout << "a";
            Bitz::enqueueMovementEvent(this,movementSpeed);
            break;
        case SDL_SCANCODE_D:
            setDirection(util::EAST);
            std::cout << "d";
            Bitz::enqueueMovementEvent(this,movementSpeed);
            break;
        case SDL_SCANCODE_SPACE:
            attack();
            break;
        //case SDL_SCANCODE_LSHIFT:
            //roll();
            //break;
        default: break;
        }
    }

//Just isn't setup in engine
void Player::roll() {
    switch (getDirection()) {
        case util::NORTH:
            Bitz::enqueueMovementEvent(this, rollDisplacement);
        break;
        case util::EAST:
            Bitz::enqueueMovementEvent(this, rollDisplacement);
        break;
        case util::SOUTH:
            Bitz::enqueueMovementEvent(this, rollDisplacement);
        break;
        case util::WEST:
            Bitz::enqueueMovementEvent(this, rollDisplacement);
        break;
        default:
            throw new std::logic_error("Unknown direction enum");
    }

    //So where this needs to become false again.
    rolling = true;

}

bool Player::isRolling() {
    return rolling;
}

void Player::endRoll() {
    rolling = false;
}

void Player::attack() {
    if (instance) {
        Bitz::enqueueAttackEvent(instance.get());
    }

}

int Player::getHitBoxSize() {
    return hitBoxSize;
}
