
//
// Created by Kyler on 8/5/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "ObserverPattern.h"


struct SDLItems {
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
    int initWidth {800}, initHeight {600}, logiWidth {1800}, logiHeight {1080};
};

class View : public Observer {
private:
    SDLItems myItems;
    bool isRunning;
    static void cleanup(const SDLItems &theItems);

public:

    View() : isRunning(false) { initialize(); };

    ~View() { endProcess(); }

    void initialize();

    SDL_Window* getWindow() const { return myItems.window; }
    SDL_Renderer* getRenderer() const { return myItems.renderer; }
    void endProcess() const;
    void Update(Subject* theChangedSubject, const std::string& thePropertyName);

};


#endif //VIEW_H
