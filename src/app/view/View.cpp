
#include "../../include/View.h"
#include "../../include/Utils.h"

std::shared_ptr<View> View::instance = nullptr;


std::shared_ptr<View> View::guiInstance() {

    //Breaks at this if
    if (instance == nullptr) {
        instance =  std::unique_ptr<View>(new View());
    }


    return instance;

}


void View::initialize() {
    //See if SDL Boots
    std::cout << "Initialize View" << std::endl;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        cleanup(myWindow);
    }

    //Make the Window
    const int initWidth{800};
    const int initHeight{600};
    myWindow.window = SDL_CreateWindow("Game", initWidth, initHeight, SDL_WINDOW_RESIZABLE);
    if (!myWindow.window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        cleanup(myWindow);
    }

    //Create the renderer
    myWindow.renderer = SDL_CreateRenderer(myWindow.window, nullptr);
    if (!myWindow.renderer) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        cleanup(myWindow);
    }

    SDL_SetRenderLogicalPresentation(myWindow.renderer, myWindow.logiWidth, myWindow.logiHeight,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);


    //Boot up SDL Audio for loading audio mixer
    std::cout << "Initialize Audio Mixer" << std::endl;
    if (!SDL_Init(SDL_INIT_AUDIO)) {
        std::cout << "Could not Initialize Audio" << std::endl;
        cleanup(myWindow);
    }

    /*
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, SDL_AUDIO_S16, MIX_DEFAULT_CHANNELS, 2048)) {
        std::cout << "Could not initialize Mixer" << std::endl;
        cleanup(myWindow);
    }
    */

    myAssets.generateAssets(myWindow);

    isRunning = true;
    //Mix_PlayMusic(myAssets.musicLoop, -1);
    std::cout << "The window is created" << std::endl;
}


void View::loadActiveSprites() {
    myAssets.characters.clear();

    for (auto character : Bitz::getEntities()) {
        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            myAssets.characters.push_back(npc);
        }
    }

    for (auto character : Bitz::getEntities()) {

        if (character->getName() == "John programmer") {
            myAssets.characters.push_back(character);
        }
    }
}

//TODO: Put this back into engine?
bool View::handleEvent(SDL_Event theEvent) {
    while (SDL_PollEvent(&theEvent)) {
        switch (theEvent.type) {

            case SDL_EVENT_QUIT: {
                isRunning = false;
                return false;
                break;
            }
            case SDL_EVENT_WINDOW_RESIZED: {
                setWindowPreFullScreen(theEvent.window.data2, theEvent.window.data1);
                break;
            }
            case SDL_EVENT_KEY_DOWN: {
                handleKeyDown(theEvent.key.scancode);
            }


            default: return false;
        }
    }
    return true;
}

//TODO: Put this back into engine?
void View::handleKeyDown(const SDL_Scancode theKey) {
    switch (theKey) {
        case SDL_SCANCODE_ESCAPE:
            isRunning = false;
            break;
        case SDL_SCANCODE_F11:
            if (!myWindow.fullscreen) {
                SDL_SetWindowFullscreen(myWindow.window, true);
            } else {
                SDL_SetWindowFullscreen(myWindow.window, false);
            }
            myWindow.fullscreen = !myWindow.fullscreen;
            break;
        default:
            Player::playerInstance()->userInput(theKey);
            break;
    }
}


void View::Update(Subject* theChangedSubject, const std::string& thePropertyName) {

    if (NPC* npc = dynamic_cast<NPC*>(theChangedSubject)) {

        if (thePropertyName == NPC::PROPERTY_LOCATION_CHANGED) {
            //Animation goes here

        } else if (thePropertyName == NPC::PROPERTY_KILLED) {
            myAssets.npcTilemapX = 5.0f * myAssets.SPRITE_SIZE;
            myAssets.npcTilemapY = 3.0f * myAssets.SPRITE_SIZE;

        } else if (thePropertyName == NPC::PROPERTY_DIRECTION_CHANGED) {
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


        }

        renderSprite(myAssets.skeleTexture, *npc);
    }
    else if (Player* player = dynamic_cast<Player*>(theChangedSubject)) {
        if (thePropertyName == Player::PROPERTY_LOCATION_CHANGED) {
            //Animate Walking?????????

        } else if (thePropertyName == Player::PROPERTY_KILLED) {
            myAssets.charTilemapX = 0.0f * myAssets.SPRITE_SIZE;
            myAssets.charTilemapY = 4.0f * myAssets.SPRITE_SIZE;

        } else if (thePropertyName == Player::PROPERTY_DIRECTION_CHANGED) {
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
            //Animation from Walking?
            myAssets.charTilemapX = 5.0f * myAssets.SPRITE_SIZE;
            //myAssets.charTilemapY = 2.0 * myAssets.spriteSize;
        }

    renderSprite(myAssets.charTexture, *player);

    }
    else if (Dungeon* dungeon = dynamic_cast<Dungeon*>(theChangedSubject)) {

        if (thePropertyName == Dungeon::PROPERTY_ROOM_CHANGE) {
            loadActiveSprites();

        }


    }


}

void View::renderSprite(SDL_Texture* theCharTexture, AbstractCharacter &theCharacter) {

    //Perform Draw Commands - Clear Screen
    SDL_SetRenderDrawColor(myWindow.renderer, 5, 255, 255, 255);
    SDL_RenderClear(myWindow.renderer);

    // draw background images
    SDL_RenderTexture(myWindow.renderer, myAssets.roomTexture, nullptr, nullptr);
    /*
    drawParalaxBackground(state.renderer, res.texBg4, gs.player().velocity.x,
    gs.bg4Scroll, 0.075f, deltaTime);
    drawParalaxBackground(state.renderer, res.texBg3, gs.player().velocity.x,
    gs.bg3Scroll, 0.150f, deltaTime);
    drawParalaxBackground(state.renderer, res.texBg2, gs.player().velocity.x,
    gs.bg2Scroll, 0.3f, deltaTime);
    */

    float posX, posY, scaleX, scaleY;

    for (auto sprite : myAssets.characters) {
        SDL_Texture* spriteTex = myAssets.grabCharTexture(sprite);
        posX = sprite->getX();
        posY = sprite->getY();
        if (sprite->getName() != "John programmer") {
            scaleX = myAssets.npcTilemapX;
            scaleY = myAssets.npcTilemapY;
        } else {
            scaleX = myAssets.charTilemapX;
            scaleY = myAssets.charTilemapY;
        }

        SDL_FRect charSizeRect{
            .x = scaleX,
            .y = scaleY,
            .w = myAssets.SPRITE_SIZE,
            .h = myAssets.SPRITE_SIZE
        };

        SDL_FRect charLocRect{
            .x = posX,
            .y = posY,
            .w = myAssets.SPRITE_SIZE*10,//160 px x 160px
            .h = myAssets.SPRITE_SIZE*10 //160 px x 160px
        };

        SDL_RenderTexture(myWindow.renderer, spriteTex, &charSizeRect,
            &charLocRect);
    }

    //Swap buffers and present screen
    SDL_RenderPresent(myWindow.renderer);
}

//This method is for other entities outside view to tell View to stop and close everything
void View::endProcess() const {
    cleanup(myWindow);
}

void View::cleanup(const windowState &theItems) {
    SDL_DestroyWindow(theItems.window);
    SDL_DestroyRenderer(theItems.renderer);
    //Mix_CloseAudio();

    SDL_Quit();
}
