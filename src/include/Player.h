//
// Created by riley on 8/17/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>


#include "AbstractCharacter.h"

/**
 * Represents the player.
 * @author Riley Hopper
 * @version 2025 August
 */
class Player : public AbstractCharacter {
public:

    /** the property name for when the player starts rolling. */
    inline static const std::string PROPERTY_CHANGED_ROLL = "I might be rolling";

    /**
     * This returns the player to users
     * @return A pointer to the player
     */
    static std::shared_ptr<Player> playerInstance();

    /**
     * This will see what key the user has inputted.
     * @param event This is the SDL event
     */
    void userInput(SDL_Event &event);

    /**
     * This takes the players current direction and rolls them
     * A roll give the player I frames.
     */
    void roll();

    /**
     *
     * @return A truthy value related to if the player is rolling
     */
    bool isRolling();

    /**
     * This stops the player from rolling.
     */
    void endRoll();

    /**
     * This method makes the player attack
     */
    void attack();




private:
    Player(const std::string &theName
        , int theMaxHealth, int theMovementSpeed);

    void Update(Subject *theChangedSubject
        , const std::string &thePropertyName) override;


    /**This is the instance of the player.*/
    static std::shared_ptr<Player> instance;


    static inline const std::string name = "John programmer";
    static inline const int startingHealth = 100;
    static inline const int movementSpeed = 5;


    /**This the amount of clock ticks the player won't take damage.*/
    const int invincibilityFrames = 3;
    /**This is the distance the roll displaces the player.*/
    const int rollDisplacement = 3;

    /**This is for if the player is currently rolling.*/
    bool rolling = false;
    /**HitBox size*/
    const int hitBoxSize = 10;

};



#endif //PLAYER_H
