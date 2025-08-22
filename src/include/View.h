
//
// Created by Kyler on 8/5/2025.
//

#ifndef VIEW_H
#define VIEW_H

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
//#include "SDL3_ttf/SDL_ttf.h"
//#include "SDL3_mixer/SDL_mixer.h"

#include "ObserverPattern.h"
#include "Player.h"
#include "Dungeon.h"
#include "Bitz.h"
#include "NPC.h"
#include <set>


/**
 *
 * @author Kyler McLees, Riley Hopper
 *
 */


//State of SDL, handles window states
struct windowState {
    //The SDL window
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
    //TODO: Change these to compensate UI?
    int initWidth {1500}, initHeight {1500}, logiWidth {1500}, logiHeight {1500};

    //Tells if window is fullscreen for window management
    bool fullscreen {false};

    //TODO: Start this true later
    bool inMenu {false};

};


//This structure holds all the textures
struct AssetHandler {
    //Size of Sprite on Tile Maps
    const float SPRITE_SIZE {16.0};

    //Vector of textures. This exists for cleanup of texture resources
    std::vector<SDL_Texture*> gameTextures;
    SDL_Texture *charTexture, *timTexture, *skeleTexture, *goblinTexture,
        *roomTexture, *loseTexture, *winTexture, *potionTexture, *killCountTexture;

    //Vector of sounds. This exists for easy cleanup of audio resources
    //std::vector<Mix_Audio*> musicFiles;
    //Mix_Music *musicLoop;


    std::vector<std::shared_ptr<AbstractCharacter>> characters;

    //Gives the texture of an Abstract Character
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


    SDL_Texture* loadSpriteImage(SDL_Renderer* theRenderer, const std::string &theFilePath) {
        SDL_Texture* texture = IMG_LoadTexture(theRenderer, theFilePath.c_str());
        if (texture == nullptr)
            return nullptr;

        gameTextures.push_back(texture);
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
        //TODO: Try SDL_SCALEMODE_LINEAR
        return texture;
    }

    /*
    Mix_Music* loadMusic(const std::string &theFilePath) {
        Mix_Music *music = Mix_LoadMUS(theFilePath.c_str());
        if (music == nullptr)
            return nullptr;

        musicFiles.push_back(music);
        return music;
    }
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

        std::cout << "The sprites are generated" << std::endl;

        //musicLoop = loadMusic("assets/Null Us All.mp3");

        std::cout << "The music is generated" << std::endl;

    }

    ~AssetHandler() {
        for (auto texture : gameTextures) {
            SDL_DestroyTexture(texture);
        }
        /*
        for (auto music : musicFiles) {
            Mix_FreeMusic(musicLoop);
        }
        */
    }

};


//8 enemies on screen, you need sprite points for them all
//They use the same or two textures

class View : public Observer {
private:
    windowState myWindow;
    AssetHandler myAssets;
    bool isRunning {false};

    static void cleanup(const windowState &theItems);

    View() { initialize(); };

    static std::shared_ptr<View> instance;

    void loadActiveSprites();

public:

    static std::shared_ptr<View> guiInstance();

    ~View() { endProcess(); }

    void initialize();
    void generateSprites();

    bool handleEvent(SDL_Event theEvent);
    void handleKeyDown(const SDL_Scancode theKey);

    SDL_Window* getWindow() const { return myWindow.window; }
    SDL_Renderer* getRenderer() const { return myWindow.renderer; }
    bool getRunning() const { return isRunning; }


    void setWindowPreFullScreen(int theWidth, int theHeight)
        { myWindow.initWidth = theWidth; myWindow.initHeight = theHeight; }

    void endProcess() const;
    void Update(Subject* theChangedSubject, const std::string &thePropertyName);
    void renderSprite(SDL_Texture *theCharTexture, AbstractCharacter &theCharacter);



};


#endif //VIEW_H
