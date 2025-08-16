
//
// Created by Kyler on 8/5/2025.
//

#ifndef VIEW_H
#define VIEW_H

#include "SDL3/SDL.h"
#include "../../include/AbstractCharacter.h"
#include "../../include/Dungeon.h"

/**
 * This Structure allows View to keep current render information for Sprites
**/
struct SpriteData {
    SDL_GPUTexture *texture;
    float x, y;
    float width, height;
    float rotation;
    bool visibleOnScreen;

    //16 by 16 is most assets in this game
    SpriteData() : texture (nullptr), x(0), y(0), width(16), height(16), rotation(0), visibleOnScreen(false) {}
};


class View : public Observer {
private:
    //SDL Window Components
    SDL_Window* myWindow;
    SDL_GPUDevice* myDevice;
    bool isRunning;

    //Graphic Pipline Components
    SDL_GPUGraphicsPipeline* myGraphicsPipeline;
    SDL_GPUBuffer* myVertexBuffer;
    SDL_GPUBuffer* myIndexBuffer;
    SDL_GPUSampler* mySampler;

    //Map of textures?
    //SDL_GPUTexture* characterTexture;

    //Needs to track characters and dungeon


public:
    //Create View with empty window, GPU device, and declare the window isn't running (false)
    View() : myWindow(nullptr), myDevice(nullptr), isRunning(false), myGraphicsPipeline(nullptr),
        myVertexBuffer(nullptr), myIndexBuffer(nullptr), mySampler(nullptr) {}

    //Window and all GPU resources will close automatically w/ Deconstructor
    ~View() = default;

    //Create the window / GPU
    void initialize();

    //Render all sprites
    void render();

    //Handle events like closing the application
    bool handleEvents();

    //Close all associated devices
    void cleanup();

    //Tells any other class that the window is open
    bool isWindowRunning() const { return isRunning; }


    //May need to implement a list to contain character information for drawSprites


    //Supporter method to be used to load sprites for drawSprites given a character or Item ID
    //UPDATE PARAMETERS so that specific sprites can be accessed. May need two IDs, the type of char
    //(i.e. monster, char, item) And the ID number.
    SDL_GPUTexture* loadTextures();
    void createRenderingPipeline();

    void observeDungeon(Dungeon* theDungeon);
    void unobserveDungeon(Dungeon* theDungeon);
    void observeCharacter(AbstractCharacter* theCharacter);
    void unobserveCharacter(AbstractCharacter* theCharacter);

    void Update(Subject* theChangedSubject, const std::string& thePropertyName);

    void drawRoom();
    void drawSprite(SDL_GPURenderPass* theRenderPass, SDL_GPUTexture* theTexture, float theX, float theY);
};


#endif //VIEW_H
