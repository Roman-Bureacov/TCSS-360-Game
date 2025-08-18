//
// Created by riley on 8/17/25.
//

#include "../../../include/Player.h"

#include <future>

#include "../../../include/Bitz.h"

std::shared_ptr<Player> Player::instance = nullptr;

std::shared_ptr<Player> Player::playerInstance() {

    if (instance == nullptr) {
        instance =  std::shared_ptr<Player>(new Player(name,
            startingHealth, movementSpeed));
    }


    return instance;
}

Player::Player(const std::string &theName
        , int theMaxHealth, int theMovementSpeed)
            : AbstractCharacter(theName, theMaxHealth, theMovementSpeed) {

    setHitbox(hitBoxSize, hitBoxSize);
}

void Player::Update(Subject *theChangedSubject
        , const std::string &thePropertyName) {}

void Player::userInput(SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
            case SDLK_W:
                setDirection(util::NORTH);
                Bitz::enqueueMovementEvent(this,-movementSpeed);
                break;
            case SDLK_S:
                setDirection(util::SOUTH);
                Bitz::enqueueMovementEvent(this,movementSpeed);
                break;
            case SDLK_A:
                setDirection(util::WEST);
                Bitz::enqueueMovementEvent(this,-movementSpeed);
                break;
            case SDLK_D:
                setDirection(util::EAST);
                Bitz::enqueueMovementEvent(this,movementSpeed);
                break;
            case SDLK_SPACE:
                attack();
                break;
            case SDLK_LSHIFT:
                roll();
                break;
            default: break;
        }
    }
}

void Player::roll() {
    switch (getDirection()) {
        case util::NORTH:
            Bitz::enqueueMovementEvent(this,getY() - rollDisplacement);
        break;
        case util::EAST:
            Bitz::enqueueMovementEvent(this,getX() + rollDisplacement);
        break;
        case util::SOUTH:
            Bitz::enqueueMovementEvent(this,getY() + rollDisplacement);
        break;
        case util::WEST:
            Bitz::enqueueMovementEvent(this,getX() - rollDisplacement);
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
    Bitz::enqueueAttackEvent(this);
}
