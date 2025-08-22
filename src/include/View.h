
//
// Created by Kyler on 8/5/2025.
//

#ifndef VIEW_H
#define VIEW_H

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "ObserverPattern.h"
#include "Player.h"
#include "Dungeon.h"
#include "Bitz.h"
#include "NPC.h"
#include <set>


/**
 * @file View.h
 * @brief Header file for the View class and related structures for game rendering
 * @author Kyler McLees, Riley Hopper
 * @date 8/5/2025
 *
 * This file contains the View class which serves as the main rendering system
 * for the game, implementing the Observer pattern to respond to game state changes.
 * It manages SDL3 window creation, texture loading, sprite rendering, and user input.
 */

/**
 * @struct windowState
 * @brief Manages SDL window properties and state information
 *
 * Contains all the necessary components for SDL window management including
 * the window itself, renderer, dimensions, and various state flags.
 */
struct windowState {
    //The main SDL window object
    SDL_Window* window {nullptr};

    //The renderer object for drawing operations
    SDL_Renderer* renderer {nullptr};

    //The dimensions of the window.
    int initWidth {1500}, initHeight {1500}, logiWidth {1500}, logiHeight {1500};

    //Tells if window is fullscreen for window management
    bool fullscreen {false};

    //Flag to indicate if in main menu. (Not implemented)
    //bool inMenu {false};

};


/**
 * @struct AssetHandler
 * @brief Manages all game textures, sprites, and asset-related functionality
 *
 * This structure handles loading, storing, and managing all graphical assets
 * including character sprites, backgrounds, UI elements, and texture animations.
 * It also manages sprite sheet coordinates for character animations.
 */
struct AssetHandler {
    //Size of Sprite on Tile Maps
    const float SPRITE_SIZE {16.0};

    //Vector of textures. This exists for cleanup of texture resources
    std::vector<SDL_Texture*> gameTextures;
    SDL_Texture *charTexture, *timTexture, *skeleTexture, *goblinTexture,
        *roomTexture, *loseTexture, *winTexture, *potionTexture, *killCountTexture;

    std::vector<std::shared_ptr<AbstractCharacter>> characters;

    //TTF_Font* font {nullptr};

    /**
         * @brief Retrieves the appropriate texture for a given character
         * @param theCharacter Shared pointer to the character object
         * @return SDL_Texture* corresponding to the character type
         *
         * Maps character names to their corresponding textures. Returns the
         * default character texture if no specific match is found.
         */
    SDL_Texture* grabCharTexture(const std::shared_ptr<AbstractCharacter> &theCharacter) {
        if (theCharacter->getName() == "John programmer")
            return charTexture;

        if (theCharacter->getName() == "Skeleton")
            return skeleTexture;

        if (theCharacter->getName() == "Goblin")
            return goblinTexture;

        if (theCharacter->getName() == "DarkLord Capual")
            return timTexture;

        return charTexture;
    }

    //Handles which section of the character Sprite Sheets are loaded
    float charTilemapX {0.0f}, charTilemapY {0.0f};

    //Handles which section of Skele / Goblin Sprite Sheets are loaded
    float npcTilemapX {0.0f}, npcTilemapY {0.0f};

    //Handles which section of Tim Sprite Sheet are loaded
    float timTilemapX {0.0f}, timTilemapY {0.0f};

    /**
     * @brief Loads a sprite image from file and configures it for rendering
     * @param theRenderer SDL renderer to create texture with
     * @param theFilePath File path to the image asset
     * @return SDL_Texture* pointer to the loaded texture, nullptr if failed
     *
     * Loads an image file using SDL_image, creates a texture from it,
     * adds it to the cleanup vector, and sets appropriate scaling mode.
     */
    SDL_Texture* loadSpriteImage(SDL_Renderer* theRenderer, const std::string &theFilePath) {
        SDL_Texture* texture = IMG_LoadTexture(theRenderer, theFilePath.c_str());
        if (texture == nullptr)
            return nullptr;

        gameTextures.push_back(texture);
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
        //TODO: Try SDL_SCALEMODE_LINEAR
        return texture;
    }

    /**
     * @brief Loads all game assets from the assets directory
     * @param theWindowState Window state containing the renderer
     *
     * Initializes all game textures by loading them from their respective
     * file paths. This includes character sprites, backgrounds, UI elements,
     * and fonts. Should be called during game initialization.
     */
    void generateAssets(const windowState &theWindowState) {
        std::cout << "Generating sprites" << std::endl;

        charTexture = loadSpriteImage(theWindowState.renderer,
            "assets/Kinght_Of_The_Pointer.png");

        timTexture = loadSpriteImage(theWindowState.renderer,
            "assets/Dark_Lord_Tom.png");

        skeleTexture = loadSpriteImage(theWindowState.renderer,
            "assets/Skelleton_Of_Null.png");

        goblinTexture = loadSpriteImage(theWindowState.renderer,
            "assets/Goblin_Of_Null.png");

        roomTexture = loadSpriteImage(theWindowState.renderer,
            "assets/TestDungeon.png");

        loseTexture = loadSpriteImage(theWindowState.renderer,
            "assets/YouLose.png");

        winTexture = loadSpriteImage(theWindowState.renderer,
            "assets/YouWin.png");

        potionTexture = loadSpriteImage(theWindowState.renderer,
            "assets/Potion.png");

        killCountTexture = loadSpriteImage(theWindowState.renderer,
            "assets/killCount.png");

        //font = TTF_OpenFont("assets/Pixelpurl.ttf", 20);

        std::cout << "The sprites are generated" << std::endl;

    }

    /**
     * @brief Destructor that cleans up all loaded textures
     *
     * Properly destroys all SDL textures and closes fonts to prevent
     * memory leaks when the AssetHandler is destroyed.
     */
    ~AssetHandler() {
        for (auto texture : gameTextures) {
            SDL_DestroyTexture(texture);
        }

        //TTF_CloseFont(font);
    }

};


/**
 * @class View
 * @brief Main rendering and display management class implementing Observer pattern
 *
 * The View class serves as the primary interface between the game logic and
 * the visual representation. It implements the Observer pattern to automatically
 * update the display when game objects change state. This class handles:
 * - SDL window and renderer management
 * - Texture and sprite rendering
 * - User input processing
 * - Game state visualization
 * - Animation coordination
 *
 * This class follows the Singleton pattern to ensure only one instance
 * manages the display system.
 */
class View : public Observer {
private:
    windowState myWindow;
    AssetHandler myAssets;

    /// Flag indicating if the game loop should continue running
    bool isRunning {false};
    ///Check and see if you've "won"
    bool canWin {false};

    /**
     * @brief Cleanup function for SDL resources
     * @param theWindow Window state containing resources to clean up
     *
     * Properly destroys SDL window, renderer, and quits SDL subsystems
     * to prevent resource leaks.
     */
    static void cleanup(const windowState &theWindow);

    /**
     * @brief Private constructor implementing singleton pattern
     *
     * Automatically calls initialize() to set up the display system.
     * Made private to prevent direct instantiation.
     */
    View() { initialize(); };

    static std::shared_ptr<View> instance;

    /**
     * @brief Loads currently active character sprites for rendering
     *
     * Clears the current character list and repopulates it with all
     * active NPCs and the player character. Called when room changes occur.
     */
    void loadActiveSprites();

public:

    /**
     * @brief Gets or creates the singleton View instance
     * @return std::shared_ptr<View> Shared pointer to the View instance
     *
     * Thread-safe singleton access method. Creates the instance if it
     * doesn't exist, otherwise returns the existing instance.
     */
    static std::shared_ptr<View> guiInstance();


    /**
     * @brief Destructor that ensures proper cleanup
     *
     * Calls endProcess() to clean up SDL resources when the View is destroyed.
     */
    ~View() { endProcess(); }

    /**
     * @brief Initializes the SDL display system
     *
     * Sets up SDL video subsystem, creates window and renderer, configures
     * logical presentation, loads assets, and prepares the system for rendering.
     * Should be called once during application startup.
     */
    void initialize();

    /**
     * @brief Placeholder method for sprite generation
     *
     * Currently unused method that may be implemented for dynamic
     * sprite generation in future versions.
     */
    void generateSprites();

    /**
     * @brief Processes SDL events and user input
     * @param theEvent SDL event structure to process
     * @return bool True if processing should continue, false to quit
     *
     * Handles window events, keyboard input, and other SDL events.
     * Updates game state based on user interactions and system events.
     */
    bool handleEvent(SDL_Event theEvent);

    /**
     * @brief Processes keyboard key press events
     * @param theKey SDL scancode of the pressed key
     *
     * Handles specific key presses including game controls, fullscreen toggle,
     * and application exit. Delegates player movement to the Player class.
     */
    void handleKeyDown(const SDL_Scancode theKey);

    /**
     * @brief Getter for the SDL window
     * @return SDL_Window* Pointer to the main game window
     */
    SDL_Window* getWindow() const { return myWindow.window; }

    /**
     * @brief Getter for the SDL renderer
     * @return SDL_Renderer* Pointer to the main renderer
     */
    SDL_Renderer* getRenderer() const { return myWindow.renderer; }

    /**
     * @brief Getter for the running state
     * @return bool True if the game should continue running
     */
    bool getRunning() const { return isRunning; }

    /**
     * @brief Sets window dimensions before fullscreen toggle
     * @param theWidth New window width
     * @param theHeight New window height
     *
     * Stores the window dimensions to restore them when exiting fullscreen mode.
     */
    void setWindowPreFullScreen(int theWidth, int theHeight)
        { myWindow.initWidth = theWidth; myWindow.initHeight = theHeight; }

    /**
     * @brief Initiates cleanup and shutdown process
     *
     * Signals the View to clean up all SDL resources and prepare for
     * application termination. Should be called before program exit.
     */
    void endProcess() const;

    /**
     * @brief Observer pattern update method
     * @param theChangedSubject Pointer to the object that changed
     * @param thePropertyName Name of the property that changed
     *
     * Responds to notifications from observed objects (NPCs, Player, Dungeon).
     * Updates sprite animations, positions, and visual states based on the
     * type of change that occurred.
     */
    void Update(Subject* theChangedSubject, const std::string &thePropertyName);

    /**
     * @brief Renders a character sprite to the screen
     * @param theCharTexture Texture to render for the character
     * @param theCharacter Reference to the character being rendered
     *
     * Main rendering method that clears the screen, draws the background,
     * and renders all active character sprites at their current positions
     * with appropriate animations.
     */
    void renderSprite(SDL_Texture *theCharTexture, AbstractCharacter &theCharacter);

    /**
     * @brief Renders the game over screen
     *
     * Displays the defeat screen when the player is killed, shows the
     * "You Lose" texture, and sets the game to stop running.
     */
    void renderLose();
};


#endif //VIEW_H
