
//
// Created by Kyler on 8/5/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "ObserverPattern.h"
#include "NPC.h"


struct SDLItems {
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
    int initWidth {800}, initHeight {600}, logiWidth {1800}, logiHeight {1080};
};

/**
 *
 * @author Kyler McLees, Riley Hopper
 *
 */

class View : public Observer {
private:
    SDLItems myItems;
    bool isRunning;

    static void cleanup(const SDLItems &theItems);

    View() : isRunning(false) { initialize(); };

    static std::shared_ptr<View> instance;



public:

    static std::shared_ptr<View> guiInstance();

    ~View() { endProcess(); }

    void initialize();

    SDL_Window* getWindow() const { return myItems.window; }
    SDL_Renderer* getRenderer() const { return myItems.renderer; }
    void endProcess() const;
    void Update(Subject* theChangedSubject, const std::string& thePropertyName);



};


#endif //VIEW_H
