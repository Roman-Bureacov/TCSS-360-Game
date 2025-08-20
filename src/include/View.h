
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
    int initWidth {1500}, initHeight {1500}, logiWidth {1500}, logiHeight {1500};

    //Different Structure probably
    //Character Sprite Handler
    float charTilemapX {0.0f}, charTilemapY {16.0f};
};


struct SpriteTextures {
    //Size of Sprite on Tile Maps
    const float charSpriteSize {16.0};

    SDL_Texture* charTexture {nullptr};
    SDL_Texture* timTexture {nullptr};
    SDL_Texture* skeleTexture {nullptr};
    SDL_Texture* goblinTexture {nullptr};
    SDL_Texture* roomTexture {nullptr};

    /*
    ~SpriteTextures() {
        SDL_DestroyTexture(charTexture);
        SDL_DestroyTexture(timTexture);
        SDL_DestroyTexture(skeleTexture);
        SDL_DestroyTexture(goblinTexture);
        SDL_DestroyTexture(roomTexture);
    }*/

};


//8 enemies on screen, you need sprite points for them all
//They use the same or two textures

/**
 *
 * @author Kyler McLees, Riley Hopper
 *
 */

class View : public Observer {
private:
    SDLItems myItems;
    SpriteTextures mySprites;
    bool isRunning {false};

    static void cleanup(const SDLItems &theItems);

    View() { initialize(); generateSprites(); };

    static std::shared_ptr<View> instance;



public:

    static std::shared_ptr<View> guiInstance();

    ~View() { endProcess(); }

    void initialize();
    void generateSprites();

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
