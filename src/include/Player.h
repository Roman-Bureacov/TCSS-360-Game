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
 * This is a struct that contains the basic stats for
 * Different player classes.
 *
 * @author Riley Hopper
 * @version August 2025
 */
struct PlayerClasses {

    /**This is the attack time the time takes.*/
    static const inline int MYPLAYERATTACKTIME = 10;

    /** Name of the Knight player character. */
    static inline const std::string MYNAMEKNIGHT = "John Programmer";
    /** Starting health value for the Knight player character. */
    static inline const int MYSTARTINGHEALTHKNIGHT = 100;
    /** Movement speed value for the Knight player character. */
    static inline const int MYMOVEMENTSPEEDKNIGHT = 35;
    /**This is the damage the player does.*/
    static inline const int MYDAMAGEKNIGHT = 10;

    /** Name of the Rogue player character. */
    static inline const std::string MYNAMEROGUE = "John Git Puller";
    /** Starting health value for the Rogue player character. */
    static inline const int MYSTARTINGHEALTHROGUE = 50;
    /** Movement speed value for the Rogue player character. */
    static inline const int MYMOVEMENTSPEEDROGUE = 50;
    /**This is the damage the player does.*/
    static inline const int MYDAMAGEROGUE = 5;

    /** Name of the Mage player character. */
    static inline const std::string MYNAMEMAGE = "John Stack Overflow";
    /** Starting health value for the Mage player character. */
    static inline const int MYSTARTINGHEALTHMAGE = 40;
    /** Movement speed value for the Mage player character. */
    static inline const int MYMOVEMENTSPEEDMAGE = 30;
    /**This is the damage the player does.*/
    static inline const int MYDAMAGEMAGE = 60;

    /** Name of the Archer player character. */
    static inline const std::string MYNAMEARCHER = "John Code Sniper";
    /** Starting health value for the Archer player character. */
    static inline const int MYSTARTINGHEALTHARCHER = 60;
    /** Movement speed value for the Archer player character. */
    static inline const int MYMOVEMENTSPEEDARCHER = 45;
    /**This is the damage the player does.*/
    static inline const int MYDAMAGEARCHER = 50;
};

/**
 * Enumerates the available player class types.
 * @author Riley Hopper.
 * @version August 2025.
 */
enum class playerTypes {
    Knight,  /**< Heavy melee fighter with high health and low speed. */
    Rogue,   /**< Agile melee fighter with high speed and low health. */
    Mage,    /**< Spellcaster with low health and moderate speed. */
    Archer   /**< Ranged attacker with balanced health and speed. */
};

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
    /**Property name used to signal when the player starts rolling. */
    inline static const std::string PROPERTY_CHANGED_ROLL = "I might be rolling";
    /**Property when the player changes classes. */
    inline static const std::string PROPERTY_CHANGE_CLASS = "I have changed my class";

    /**This is how much health is healed by a potion.*/
    inline static const int MYPOTIONSTRENGTH = 20;
    
    /** This is the amount of healing potions the player has.*/
    int myPotionAmount = 0;
    int the_max_health_{};

    /**
     * Retrieves the singleton instance of the player.
     * @return A shared pointer to the player instance.
     */
    static std::shared_ptr<Player> playerInstance();

    /**
     * Processes user input events.
     * Handles movement, rolling, and attacking based on key presses.
     * @param theCode key code of the key pressed.
     */
    void userInput(int theCode);

    /**
     * Initiates a roll in the current movement direction.
     * Grants temporary invincibility frames during the roll.
     */
    void roll();

    /**
     * Checks if the player is currently rolling.
     * @return True if rolling, false otherwise.
     */
    bool isRolling() const;

    /**
     * Ends the rolling state and removes invincibility.
     */
    void endRoll();

    /**
     * Uses a potion the player has.
     */
    void usePotion();

    /**
     * This give one potion to the player.
     */
    void givePotion();

    /**
     * This gives you the mount of potions the player has.
     * @return The amount of potions the player has.
     */
    int getPotionAmount() const;

    /**
     * This will set the amount of potions the player has.
     * @param theAmount the amount of potions the player should have.
     */
    void setPotionAmount(int theAmount);

    /**
     * Executes an attack action.
     * Uses the player's weapon hitbox to detect collisions.
     */
    static void attack();

    /**
     * A getter for the players hitBoxSize for testing
     */
    int getHitBoxSize() const;

    /**
     * This sets the players class.
     * @param myType This is the class type.
     */
    void setClass(playerTypes myType);

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
    static std::shared_ptr<Player> myInstance;

    /** Number of ticks the player remains invincible during a roll. */
    const int MYINCINCIBILITYFRAMES = 3;
    /** Distance the player moves during a roll. */
    const int ROLLDISPLACEMENT = 3;

    /** Indicates whether the player is currently rolling. */
    bool myRolling = false;

    /** Size of the player's hitbox. */
    const int MYHITBOXSIZE = 100;

    /** Hitbox used for the player's weapon during attacks. */
    Hitbox PlayerWeaponHitbox = Hitbox(100, 100);


    /**These are the default for the player.*/
    /**Name of the Knight player character. */
    static inline const std::string MYNAME = "John programmer";
    /** Starting health value for the Knight player character. */
    static inline const int MYSTARTINGHEALTH = 100;
    /** Movement speed value for the Knight player character. */
    static inline const int MYMOVEMENTSPEED = 35;




};

#endif // PLAYER_H
