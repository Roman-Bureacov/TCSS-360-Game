
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
        cleanup(myItems);
    }

    //Make the Window
    const int initWidth{800};
    const int initHeight{600};
    myItems.window = SDL_CreateWindow("Game", initWidth, initHeight, SDL_WINDOW_RESIZABLE);
    if (!myItems.window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        cleanup(myItems);
    }

    //Create the renderer
    myItems.renderer = SDL_CreateRenderer(myItems.window, nullptr);
    if (!myItems.renderer) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        cleanup(myItems);
    }
    //SDL_SetRenderVSync(myItems.renderer, 1); //Possible

    SDL_SetRenderLogicalPresentation(myItems.renderer, myItems.logiWidth, myItems.logiHeight,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);


    // initialize the SDL_mixer library
    /*
    if (!Mix_OpenAudio(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating audio device", state.window);
        cleanup(state);
        initSuccess = false;
    }
    */


    isRunning = true;
    std::cout << "The window is created" << std::endl;
}


void View::generateSprites() {
    std::cout << "Generating sprites" << std::endl;

    mySprites.charTexture = IMG_LoadTexture(myItems.renderer,
        "assets/Kinght_Of_The_Pointer.png");
    SDL_SetTextureScaleMode(mySprites.charTexture, SDL_SCALEMODE_NEAREST);
    std::cout << "The Player are generated" << std::endl;


    mySprites.timTexture = IMG_LoadTexture(myItems.renderer,
        "assets/Dark_Lord_Tom.png");
    SDL_SetTextureScaleMode(mySprites.timTexture, SDL_SCALEMODE_NEAREST);
    std::cout << "The Tim are generated" << std::endl;


    mySprites.skeleTexture = IMG_LoadTexture(myItems.renderer,
        "assets/Skelleton_Of_Null.png");
    SDL_SetTextureScaleMode(mySprites.skeleTexture, SDL_SCALEMODE_NEAREST);
    std::cout << "The Skeleton are generated" << std::endl;


    mySprites.goblinTexture = IMG_LoadTexture(myItems.renderer,
        "assets/Goblin_Of_Null.png");
    SDL_SetTextureScaleMode(mySprites.goblinTexture, SDL_SCALEMODE_NEAREST);
    std::cout << "The Goblin are generated" << std::endl;


    mySprites.roomTexture = IMG_LoadTexture(myItems.renderer,
        "assets/Tiling_dungeon_Tile_Set.png");
    SDL_SetTextureScaleMode(mySprites.roomTexture, SDL_SCALEMODE_NEAREST);


    std::cout << "The sprites are generated" << std::endl;
}


bool View::handleEvent(SDL_Event theEvent) {
    while (SDL_PollEvent(&theEvent)) {
        switch (theEvent.type) {

            case SDL_EVENT_QUIT: {
                isRunning = false;
                return false;
                break;
            }
            case SDL_EVENT_WINDOW_RESIZED: {
                myItems.initHeight = theEvent.window.data1;
                myItems.initWidth = theEvent.window.data2;
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


void View::handleKeyDown(const SDL_Scancode theKey) {
    switch (theKey) {
        case SDL_SCANCODE_ESCAPE:
            isRunning = false;
            break;
        case SDL_SCANCODE_F11:
            SDL_SetWindowFullscreen(myItems.window, true);
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
            myItems.npcTilemapX = 5.0f * mySprites.spriteSize;
            myItems.npcTilemapY = 3.0f * mySprites.spriteSize;

        } else if (thePropertyName == NPC::PROPERTY_DIRECTION_CHANGED) {
            util::Direction direction = npc->getDirection();
            switch (direction) {
                case util::SOUTH: {
                    myItems.npcTilemapX = 0.0f * mySprites.spriteSize;
                    myItems.npcTilemapY = 3.0f * mySprites.spriteSize;
                    break;
                }
                case util::EAST: {
                    myItems.npcTilemapX = 0.0f * mySprites.spriteSize;
                    myItems.npcTilemapY = 0.0f * mySprites.spriteSize;
                    break;
                }
                case util::WEST: {
                    myItems.npcTilemapX = 0.0f * mySprites.spriteSize;
                    myItems.npcTilemapY = 1.0f * mySprites.spriteSize;
                    break;
                }
                case util::NORTH: {
                    myItems.npcTilemapX = 0.0f * mySprites.spriteSize;
                    myItems.npcTilemapY = 2.0f * mySprites.spriteSize;
                    break;
                }
            }
        } else if (thePropertyName == NPC::PROPERTY_I_ATTACKED) {


        }

        renderSprite(mySprites.skeleTexture, static_cast<AbstractCharacter*>(theChangedSubject));
    }
    else if (Player* player = dynamic_cast<Player*>(theChangedSubject)) {
        if (thePropertyName == Player::PROPERTY_LOCATION_CHANGED) {
            //Animate Walking?????????

        } else if (thePropertyName == Player::PROPERTY_KILLED) {
            myItems.charTilemapX = 0.0f * mySprites.spriteSize;
            myItems.charTilemapY = 4.0f * mySprites.spriteSize;

        } else if (thePropertyName == Player::PROPERTY_DIRECTION_CHANGED) {
            util::Direction direction = player->getDirection();
            switch (direction) {
                case util::SOUTH: {
                    myItems.charTilemapX = 0.0f * mySprites.spriteSize;
                    myItems.charTilemapY = 3.0f * mySprites.spriteSize;
                    break;
                }
                case util::EAST: {
                    myItems.charTilemapX = 0.0f * mySprites.spriteSize;
                    myItems.charTilemapY = 0.0f * mySprites.spriteSize;
                    break;
                }
                case util::WEST: {
                    myItems.charTilemapX = 0.0f * mySprites.spriteSize;
                    myItems.charTilemapY = 1.0f * mySprites.spriteSize;
                    break;
                }
                case util::NORTH: {
                    myItems.charTilemapX = 0.0f * mySprites.spriteSize;
                    myItems.charTilemapY = 2.0f * mySprites.spriteSize;
                    break;
                }
            }

        } else if (thePropertyName == Player::PROPERTY_I_ATTACKED) {
            //Animation from Walking?
            myItems.charTilemapX = 5.0f * mySprites.spriteSize;
            //myItems.charTilemapY = 2.0 * mySprites.spriteSize;
        }

    renderSprite(mySprites.charTexture, static_cast<AbstractCharacter*>(theChangedSubject));

    }
    else if (Dungeon* dungeon = dynamic_cast<Dungeon*>(theChangedSubject)) {

        if (thePropertyName == Dungeon::PROPERTY_ROOM_CHANGE) {


        }


    }


}

void View::renderSprite(SDL_Texture* theCharTexture, AbstractCharacter* theCharacter) {

//skeleton

    float posX = theCharacter->getX();
    float posY = theCharacter->getY();
    float scaleX, scaleY;
    if (theCharacter->getName() != "John programmer") {
        scaleX = myItems.npcTilemapX;
        scaleY = myItems.npcTilemapY;
    } else {
        scaleX = myItems.charTilemapX;
        scaleY = myItems.charTilemapY;
    }

    //Perform Draw Commands
    SDL_SetRenderDrawColor(myItems.renderer, 5, 255, 255, 255);
    SDL_RenderClear(myItems.renderer);

    SDL_FRect charSizeRect{
        .x = scaleX,
        .y = scaleY,
        .w = mySprites.spriteSize,
        .h = mySprites.spriteSize
    };

    SDL_FRect charLocRect{
        .x = posX,
        .y = posY,
        .w = mySprites.spriteSize*10,//160 px x 160px
        .h = mySprites.spriteSize*10 //160 px x 160px
    };

    SDL_RenderTexture(myItems.renderer, theCharTexture, &charSizeRect,
        &charLocRect);

    //Swap buffers and present screen
    SDL_RenderPresent(myItems.renderer);
}



void View::endProcess() const {
    cleanup(myItems);
}

void View::cleanup(const SDLItems &theItems) {
    SDL_DestroyWindow(theItems.window);
    SDL_DestroyRenderer(theItems.renderer);

    SDL_Quit();
}
