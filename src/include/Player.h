//
// Created by riley on 8/17/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <future>

#include "AbstractCharacter.h"
#include "Bitz.h"
#include "View.h"

/**
 * Represents the player character in the game.
 * Handles user input, movement, rolling, and attacking behavior.
 * Implements observer pattern via Subject updates.
 *
 * @author Riley Hopper
 * @version August 2025
 */
class Player : public AbstractCharacter {
public:
    /** Property name used to signal when the player starts rolling. */
    inline static const std::string PROPERTY_CHANGED_ROLL = "I might be rolling";

    /**
     * Retrieves the singleton instance of the player.
     * @return A shared pointer to the player instance.
     */
    static std::shared_ptr<Player> playerInstance();

    /**
     * Processes user input events.
     * Handles movement, rolling, and attacking based on key presses.
     * @param keyEvent
     * @param event SDL event containing user input data.
     */
    void userInput(SDL_Scancode keyEvent);

    /**
     * Initiates a roll in the current movement direction.
     * Grants temporary invincibility frames during the roll.
     */
    void roll();

    /**
     * Checks if the player is currently rolling.
     * @return True if rolling, false otherwise.
     */
    bool isRolling();

    /**
     * Ends the rolling state and removes invincibility.
     */
    void endRoll();

    /**
     * Executes an attack action.
     * Uses the player's weapon hitbox to detect collisions.
     */
    void attack();

private:
    /**
     * Constructs the player character with specified attributes.
     * @param theName The name of the player.
     * @param theMaxHealth The maximum health value.
     * @param theMovementSpeed The movement speed value.
     */
    Player(const std::string &theName, int theMaxHealth, int theMovementSpeed);

    /**
     * Responds to property changes from observed subjects.
     * Used to react to game state updates.
     * @param theChangedSubject The subject that triggered the update.
     * @param thePropertyName The name of the changed property.
     */
    void Update(Subject *theChangedSubject, const std::string &thePropertyName) override;

    /** Singleton instance of the player. */
    static std::shared_ptr<Player> instance;

    /** Default name of the player character. */
    static inline const std::string name = "John programmer";
    /** Starting health value for the player. */
    static inline const int startingHealth = 100;
    /** Movement speed value for the player. */
    static inline const int movementSpeed = 75;

    /** Number of ticks the player remains invincible during a roll. */
    const int invincibilityFrames = 3;
    /** Distance the player moves during a roll. */
    const int rollDisplacement = 3;

    /** Indicates whether the player is currently rolling. */
    bool rolling = false;

    /** Size of the player's hitbox. */
    const int hitBoxSize = 10;

    /** Hitbox used for the player's weapon during attacks. */
    Hitbox PlayerWeaponHitbox = Hitbox(10, 10);
};

#endif // PLAYER_H
