//
// Created by riley on 8/17/25.
//

#include "../../../include/Player.h"

std::unique_ptr<Player> Player::instance = nullptr;

Player * Player::playerInstance() {

    if (instance == nullptr) {
        instance =  std::unique_ptr<Player>(new Player(name,
            startingHealth, movementSpeed));
    }


    return instance.get();
}

Player::Player(const std::string &theName
        , int theMaxHealth, int theMovementSpeed)
            : AbstractCharacter(theName, theMaxHealth, theMovementSpeed) {}

void Player::Update(Subject *theChangedSubject
        , const std::string &thePropertyName) {}

void Player::userInput(SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
            case SDLK_W: setY(getY() - movementSpeed);setDirection(util::NORTH); break;
            case SDLK_S: setY(getY() + movementSpeed);setDirection(util::SOUTH); break;
            case SDLK_A: setX(getX() - movementSpeed);setDirection(util::WEST); break;
            case SDLK_D: setX(getX() + movementSpeed);setDirection(util::EAST); break;
            case SDLK_SPACE: roll(); break;
            default: break;
        }
    }
}

void Player::roll() {
    util::Direction dir = getDirection();

    if (dir == util::NORTH) {
        setY(getY() + rollDisplacement);

    } else if (dir == util::SOUTH) {
        setY(getY() - rollDisplacement);
    } else if (dir == util::WEST) {
        setX(getX() - rollDisplacement);
    } else if (dir == util::EAST) {
        setX(getX() + rollDisplacement);
    } else {
        //throw an exception
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
