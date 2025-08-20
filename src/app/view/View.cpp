
/**
 *
 * @author Kyler McLees
 *
 */

#include "../../include/View.h"


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

    isRunning = true;
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


            default: return false;
        }
    }
    return true;
}



void View::Update(Subject* theChangedSubject, const std::string& thePropertyName) {

}


void View::endProcess() const {
    cleanup(myItems);
}

void View::cleanup(const SDLItems &theItems) {
    SDL_DestroyWindow(theItems.window);
    SDL_DestroyRenderer(theItems.renderer);

    SDL_Quit();
}
