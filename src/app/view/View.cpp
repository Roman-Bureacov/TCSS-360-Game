

#include "../../include/View.h"

#include "../../include/Dungeon.h"


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


    SDL_SetRenderLogicalPresentation(myItems.renderer, myItems.logiWidth, myItems.logiHeight,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);
}


void View::Update(Subject* theChangedSubject, const std::string& thePropertyName) {

    if (NPC* npc = dynamic_cast<NPC*>(theChangedSubject)) {
        if (thePropertyName == NPC::PROPERTY_LOCATION_CHANGED) {


        } else if (thePropertyName == NPC::PROPERTY_KILLED) {


        } else if (thePropertyName == NPC::PROPERTY_DIRECTION_CHANGED) {


        } else if (thePropertyName == NPC::PROPERTY_I_ATTACKED) {


        }


    } else if (Player* player = dynamic_cast<Player*>(theChangedSubject)) {

        if (thePropertyName == Player::PROPERTY_LOCATION_CHANGED) {


        } else if (thePropertyName == Player::PROPERTY_KILLED) {


        } else if (thePropertyName == Player::PROPERTY_DIRECTION_CHANGED) {


        } else if (thePropertyName == Player::PROPERTY_I_ATTACKED) {


        }

    } else if (Dungeon* dungeon = dynamic_cast<Dungeon*>(theChangedSubject)) {

        if (thePropertyName == Dungeon::PROPERTY_ROOM_CHANGE) {


        }


    }


}


void View::endProcess() const {
    cleanup(myItems);
}

void View::cleanup(const SDLItems &theItems) {
    SDL_DestroyWindow(theItems.window);
    SDL_DestroyRenderer(theItems.renderer);

    SDL_Quit();
}
