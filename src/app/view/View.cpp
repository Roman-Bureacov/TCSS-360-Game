
#include "../../include/View.h"
#include "../../include/Utils.h"
// Initialize static instance pointer to nullptr
std::shared_ptr<View> View::instance = nullptr;

/**
 * @brief Singleton accessor method for the View instance
 * @return std::shared_ptr<View> Shared pointer to the single View instance
 *
 * Implements thread-safe singleton pattern. Creates a new View instance
 * if one doesn't exist, otherwise returns the existing instance.
 * The instance is created using a unique_ptr with private constructor access.
 */
std::shared_ptr<View> View::guiInstance() {
    // Create instance if it doesn't exist (singleton pattern)
    if (instance == nullptr) {
        instance = std::unique_ptr<View>(new View());
    }

    return instance;
}

/**
 * @brief Initializes the SDL display system and game window
 *
 * This method performs the complete setup of the rendering system:
 * 1. Initializes SDL video subsystem
 * 2. Creates the game window with specified dimensions
 * 3. Creates the renderer with hardware acceleration
 * 4. Sets up logical presentation for consistent scaling
 * 5. Loads all game assets
 * 6. Sets the running flag to true
 *
 * If any step fails, displays error messages and cleans up resources.
 */
void View::initialize() {
    //See if SDL Boots
    std::cout << "Initialize View" << std::endl;
    // Initialize SDL video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        cleanup(myWindow);
    }

    // Create the main game window
    const int initWidth{800};   // Initial window width
    const int initHeight{600};  // Initial window height
    myWindow.window = SDL_CreateWindow("Game", initWidth, initHeight, SDL_WINDOW_RESIZABLE);
    if (!myWindow.window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        cleanup(myWindow);
    }

    // Create the renderer for drawing operations
    myWindow.renderer = SDL_CreateRenderer(myWindow.window, nullptr);
    if (!myWindow.renderer) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        cleanup(myWindow);
    }

    // Set up logical presentation for consistent rendering across different screen sizes
    SDL_SetRenderLogicalPresentation(myWindow.renderer, myWindow.logiWidth, myWindow.logiHeight,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // TTF initialization (currently disabled)
    /*
    if (!TTF_Init()) {
        cleanup(myWindow);
    }*/

    // Load all game assets (textures, sprites, etc.)
    myAssets.generateAssets(myWindow);

    // Set running flag to true to start the game loop
    isRunning = true;
    std::cout << "The window is created" << std::endl;
}

/**
 * @brief Loads all currently active character sprites for rendering
 *
 * This method clears the current character list and repopulates it with:
 * 1. All active NPCs from the game entities
 * 2. The player character ("John programmer")
 *
 * Called whenever the game state changes (like room transitions) to ensure
 * only relevant sprites are rendered.
 */
void View::loadActiveSprites() {
    // Clear existing character list
    myAssets.characters.clear();

    // Add all active NPCs to the render list
    for (auto character : Bitz::getEntities()) {
        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            myAssets.characters.push_back(npc);
        }
    }

    // Add the player character to the render list
    for (auto character : Bitz::getEntities()) {
        if (character->getName() == "John programmer") {
            myAssets.characters.push_back(character);
        }
    }
}

/**
 * @brief Main event handling method for SDL events
 * @param theEvent SDL_Event structure containing event data
 * @return bool True if event processing should continue, false to quit
 *
 * Processes all pending SDL events including:
 * - Window close events (SDL_EVENT_QUIT)
 * - Window resize events (SDL_EVENT_WINDOW_RESIZED)
 * - Keyboard input events (SDL_EVENT_KEY_DOWN)
 *
 * TODO: Consider moving this back into the main engine class
 */
bool View::handleEvent(SDL_Event theEvent) {
    while (SDL_PollEvent(&theEvent)) {
        switch (theEvent.type) {
            case SDL_EVENT_QUIT: {
                // User clicked window close button
                isRunning = false;
                return false;
                break;
            }
            case SDL_EVENT_WINDOW_RESIZED: {
                // Window was resized, store new dimensions
                setWindowPreFullScreen(theEvent.window.data2, theEvent.window.data1);
                break;
            }
            case SDL_EVENT_KEY_DOWN: {
                // Key was pressed, handle the input
                handleKeyDown(theEvent.key.scancode);
            }

            default:
                return false;
        }
    }
    return true;
}

/**
 * @brief Handles keyboard key press events
 * @param theKey SDL_Scancode representing the pressed key
 *
 * Processes specific keyboard inputs:
 * - ESC: Quit the application
 * - F11: Toggle fullscreen mode
 * - Other keys: Pass to player for movement/actions
 *
 * TODO: Consider moving this back into the main engine class
 */
void View::handleKeyDown(const SDL_Scancode theKey) {
    switch (theKey) {
        case SDL_SCANCODE_ESCAPE:
            // ESC key pressed - quit the game
            isRunning = false;
            break;

        case SDL_SCANCODE_F11:
            // F11 key pressed - toggle fullscreen
            if (!myWindow.fullscreen) {
                SDL_SetWindowFullscreen(myWindow.window, true);
            } else {
                SDL_SetWindowFullscreen(myWindow.window, false);
            }
            myWindow.fullscreen = !myWindow.fullscreen;
            break;

        default:
            // Pass other keys to the player for handling
            Player::playerInstance()->userInput(theKey);
            break;
    }
}

/**
 * @brief Observer pattern update method - responds to game state changes
 * @param theChangedSubject Pointer to the object that notified of changes
 * @param thePropertyName String identifier of what property changed
 *
 * This method implements the Observer pattern, responding to notifications from:
 * - NPCs: Location changes, deaths, direction changes, attacks
 * - Player: Location changes, death, direction changes, attacks
 * - Dungeon: Room changes
 *
 * Updates sprite animations and positions based on the type of change.
 */
void View::Update(Subject* theChangedSubject, const std::string& thePropertyName) {

    // Handle NPC state changes
    if (NPC* npc = dynamic_cast<NPC*>(theChangedSubject)) {

        if (thePropertyName == NPC::PROPERTY_LOCATION_CHANGED) {
            // NPC moved - animation could go here

        } else if (thePropertyName == NPC::PROPERTY_KILLED) {
            // NPC was killed - set death sprite coordinates
            myAssets.npcTilemapX = 5.0f * myAssets.SPRITE_SIZE;
            myAssets.npcTilemapY = 3.0f * myAssets.SPRITE_SIZE;

        } else if (thePropertyName == NPC::PROPERTY_DIRECTION_CHANGED) {
            // NPC changed direction - update sprite to match facing direction
            util::Direction direction = npc->getDirection();
            switch (direction) {
                case util::SOUTH: {
                    myAssets.npcTilemapX = 0.0f * myAssets.SPRITE_SIZE;
                    myAssets.npcTilemapY = 3.0f * myAssets.SPRITE_SIZE;
                    break;
                }
                case util::EAST: {
                    myAssets.npcTilemapX = 0.0f * myAssets.SPRITE_SIZE;
                    myAssets.npcTilemapY = 0.0f * myAssets.SPRITE_SIZE;
                    break;
                }
                case util::WEST: {
                    myAssets.npcTilemapX = 0.0f * myAssets.SPRITE_SIZE;
                    myAssets.npcTilemapY = 1.0f * myAssets.SPRITE_SIZE;
                    break;
                }
                case util::NORTH: {
                    myAssets.npcTilemapX = 0.0f * myAssets.SPRITE_SIZE;
                    myAssets.npcTilemapY = 2.0f * myAssets.SPRITE_SIZE;
                    break;
                }
            }
        } else if (thePropertyName == NPC::PROPERTY_I_ATTACKED) {
            // NPC performed an attack - attack animation could go here
        }

        // Render the NPC with skeleton texture
        renderSprite(myAssets.skeleTexture, *npc);
    }
    // Handle Player state changes
    else if (Player* player = dynamic_cast<Player*>(theChangedSubject)) {
        if (thePropertyName == Player::PROPERTY_LOCATION_CHANGED) {
            // Player moved - walking animation could go here

        } else if (thePropertyName == Player::PROPERTY_KILLED) {
            // Player died - set death sprite and show game over
            myAssets.charTilemapX = 0.0f * myAssets.SPRITE_SIZE;
            myAssets.charTilemapY = 4.0f * myAssets.SPRITE_SIZE;
            renderLose();

        } else if (thePropertyName == Player::PROPERTY_DIRECTION_CHANGED) {
            // Player changed direction - update sprite to match facing direction
            util::Direction direction = player->getDirection();
            switch (direction) {
                case util::SOUTH: {
                    myAssets.charTilemapX = 0.0f * myAssets.SPRITE_SIZE;
                    myAssets.charTilemapY = 3.0f * myAssets.SPRITE_SIZE;
                    break;
                }
                case util::EAST: {
                    myAssets.charTilemapX = 0.0f * myAssets.SPRITE_SIZE;
                    myAssets.charTilemapY = 0.0f * myAssets.SPRITE_SIZE;
                    break;
                }
                case util::WEST: {
                    myAssets.charTilemapX = 0.0f * myAssets.SPRITE_SIZE;
                    myAssets.charTilemapY = 1.0f * myAssets.SPRITE_SIZE;
                    break;
                }
                case util::NORTH: {
                    myAssets.charTilemapX = 0.0f * myAssets.SPRITE_SIZE;
                    myAssets.charTilemapY = 2.0f * myAssets.SPRITE_SIZE;
                    break;
                }
            }

        } else if (thePropertyName == Player::PROPERTY_I_ATTACKED) {
            // Player performed an attack - set attack animation sprite
            myAssets.charTilemapX = 5.0f * myAssets.SPRITE_SIZE;
            // Y coordinate could be adjusted for different attack directions
            //myAssets.charTilemapY = 2.0 * myAssets.spriteSize;
        }

        // Render the player with character texture
        renderSprite(myAssets.charTexture, *player);
    }
    // Handle Dungeon state changes
    else if (Dungeon* dungeon = dynamic_cast<Dungeon*>(theChangedSubject)) {
        if (thePropertyName == Dungeon::PROPERTY_ROOM_CHANGE) {
            // Room changed - reload active sprites for new room
            loadActiveSprites();
        }
        else if (thePropertyName == Dungeon::PROPERTY_WIN) {
            if (canWin)
                isRunning = false;
        }
    }
}

/**
 * @brief Main sprite rendering method
 * @param theCharTexture The texture to use for rendering (may be unused in current implementation)
 * @param theCharacter Reference to the character being rendered (may be unused in current implementation)
 *
 * This method performs the complete rendering pipeline:
 * 1. Clears the screen with background color
 * 2. Renders the room/dungeon background
 * 3. Renders all active character sprites with proper positioning and animation
 * 4. Presents the final frame to the screen
 *
 * Note: The parameters may not be directly used as the method renders all active sprites
 */
void View::renderSprite(SDL_Texture* theCharTexture, AbstractCharacter &theCharacter) {

    // Clear the screen with cyan background color
    SDL_SetRenderDrawColor(myWindow.renderer, 5, 255, 255, 255);
    SDL_RenderClear(myWindow.renderer);

    // Draw the room/dungeon background
    SDL_RenderTexture(myWindow.renderer, myAssets.roomTexture, nullptr, nullptr);

    // Text rendering code (currently disabled)
    /*
    SDL_Color White = { 200, 200, 200 };
    SDL_Surface* textSurface = TTF_RenderText_Blended(myAssets.font, "HELLO", sizeof("HELLO"), White);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(myWindow.renderer, textSurface);
    SDL_DestroySurface(textSurface);
    SDL_FRect dstRect = { 100,100, 200, 80 };
    SDL_RenderTexture(myWindow.renderer, textTexture, nullptr, &dstRect);
    SDL_DestroyTexture(textTexture);
    */

    // Variables for sprite positioning and animation
    float posX, posY, scaleX, scaleY;

    // Render all active character sprites
    for (auto sprite : myAssets.characters) {
        // Get the appropriate texture for this character
        SDL_Texture* spriteTex = myAssets.grabCharTexture(sprite);

        // Get character's world position
        posX = sprite->getX();
        posY = sprite->getY();

        // Determine which sprite animation frame to use
        if (sprite->getName() != "John programmer") {
            // Use NPC animation coordinates for enemies
            scaleX = myAssets.npcTilemapX;
            scaleY = myAssets.npcTilemapY;
        } else {
            // Use player animation coordinates for the main character
            scaleX = myAssets.charTilemapX;
            scaleY = myAssets.charTilemapY;
        }

        // Define source rectangle (which part of sprite sheet to use)
        SDL_FRect charSizeRect{
            .x = scaleX,                    // X offset in sprite sheet
            .y = scaleY,                    // Y offset in sprite sheet
            .w = myAssets.SPRITE_SIZE,      // Width of sprite (16px)
            .h = myAssets.SPRITE_SIZE       // Height of sprite (16px)
        };

        // Define destination rectangle (where to draw on screen)
        SDL_FRect charLocRect{
            .x = posX,                          // Screen X position
            .y = posY,                          // Screen Y position
            .w = myAssets.SPRITE_SIZE*10,       // Scaled width (160px)
            .h = myAssets.SPRITE_SIZE*10        // Scaled height (160px)
        };

        // Render the sprite to the screen
        SDL_RenderTexture(myWindow.renderer, spriteTex, &charSizeRect, &charLocRect);
    }

    // Present the rendered frame to the screen
    SDL_RenderPresent(myWindow.renderer);
}

/**
 * @brief Renders the game over screen when the player is defeated
 *
 * Displays the "You Lose" screen with appropriate positioning and then
 * sets the game to stop running. This method:
 * 1. Clears the screen
 * 2. Renders the room background
 * 3. Displays the "You Lose" texture prominently
 * 4. Presents the final frame
 * 5. Sets isRunning to false to end the game loop
 */
void View::renderLose() {

    // Clear the screen with cyan background color
    SDL_SetRenderDrawColor(myWindow.renderer, 5, 255, 255, 255);
    SDL_RenderClear(myWindow.renderer);

    // Draw the room background
    SDL_RenderTexture(myWindow.renderer, myAssets.roomTexture, nullptr, nullptr);

    // Define source rectangle for "You Lose" texture
    SDL_FRect charSizeRect{
        .x = 64,
        .y = 16,
        .w = myAssets.SPRITE_SIZE,
        .h = myAssets.SPRITE_SIZE
    };

    SDL_FRect charLocRect{
        .x = 750-64,
        .y = 750-16,
        .w = myAssets.SPRITE_SIZE*4*10,//160 px x 160px
        .h = myAssets.SPRITE_SIZE*10 //160 px x 160px
    };

    SDL_RenderTexture(myWindow.renderer, myAssets.loseTexture, &charSizeRect,
        &charLocRect);

    //Swap buffers and present screen
    SDL_RenderPresent(myWindow.renderer);

    isRunning = false;
}

//This method is for other entities outside view to tell View to stop and close everything
void View::endProcess() const {
    cleanup(myWindow);
}

//This program closes window, renderer, and SDL from the Window struct handled by View
void View::cleanup(const windowState &theWindow) {
    SDL_DestroyWindow(theWindow.window);
    SDL_DestroyRenderer(theWindow.renderer);
    //TTF_Quit();

    SDL_Quit();
}
