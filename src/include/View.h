
//
// Created by Kyler on 8/5/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "ObserverPattern.h"
#include "Player.h"
#include "Dungeon.h"
#include "NPC.h"


struct SDLItems {
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
    int initWidth {800}, initHeight {600}, logiWidth {800}, logiHeight {800};
    const float charSpriteSize {16.0};
};

/**
 *
 * @author Kyler McLees, Riley Hopper
 *
 */

class View : public Observer {
private:
    SDLItems myItems;
    bool isRunning {false};

    static void cleanup(const SDLItems &theItems);

    View() { initialize(); };

    static std::shared_ptr<View> instance;



public:

    static std::shared_ptr<View> guiInstance();

    ~View() { endProcess(); }

    void initialize();

    bool handleEvent(SDL_Event theEvent);
    void handleKeyDown(const SDL_Scancode theKey);

    SDL_Window* getWindow() const { return myItems.window; }
    SDL_Renderer* getRenderer() const { return myItems.renderer; }
    bool getRunning() const { return isRunning; }

    void endProcess() const;
    void Update(Subject* theChangedSubject, const std::string& thePropertyName);
    void renderCharacter(SDL_Texture *theCharTexture);



};


#endif //VIEW_H
