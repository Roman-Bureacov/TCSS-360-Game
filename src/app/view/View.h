
//
// Created by Kyler on 8/5/2025.
//

#ifndef VIEW_H
#define VIEW_H

#include "SDL3/SDL.h"

void runWindow();

class View {
private:
    //The window object
    SDL_Window* window;
    //Use the Graphics Device on Machine
    SDL_GPUDevice* device;
    //Is the window running?
    bool isRunning;

    // TODO: See if this is necessary
    /*characterTexture(nullptr), graphicsPipeline(nullptr),
        vertexBuffer(nullptr),
        */
    //SDL_GPUTexture* characterTexture;
    //SDL_GPUGraphicsPipeline* graphicsPipeline;
    //SDL_GPUBuffer* vertexBuffer;

public:
    //Create View with empty window, GPU device, and declare the window isn't running (false)
    View() : window(nullptr), device(nullptr), isRunning(false) {}

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

    //Will use information given to it to draw the room that character + enemies are in
    void drawRoom();

    //Will use the information it knows of models to loadTextures on the screen
    //Responsible for moving objects and updating sprites
    void drawSprite(SDL_GPURenderPass* renderPass, SDL_GPUTexture* texture, float x, float y);
};


#endif //VIEW_H
