//
// Created by iwant on 7/7/2025.
//

// Example program:
// Using SDL3 to create an application window

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <thread>


#include "include/Room.h"
#include "include/Dungeon.h"
#include "include/View.h"
#include "include/Bitz.h"
#include "include/Clock.h"


int main(int argc, char* argv[]) {

    std::cout << "Hello World!" << std::endl;

    View* gameView = View::guiInstance().get();

    //Loading Image
    SDL_Texture *charTexture = IMG_LoadTexture(gameView->getRenderer(),
        "assets/Kinght_Of_The_Pointer.png");
    SDL_SetTextureScaleMode(charTexture, SDL_SCALEMODE_NEAREST);

    //setup Game Data
    float playerX {150.0}, playerY {150.0};
    const float charSize {16.0};

    //Game Loop
    bool gameRunning = true;
    do {
        SDL_Event gameEvent { 0 };
        gameView->handleEvent(gameEvent);

        if (!gameView->getRunning()) {
            gameRunning = false;
        }

        //Perform Draw Commands
        SDL_SetRenderDrawColor(gameView->getRenderer(), 5, 255, 255, 255);
        SDL_RenderClear(gameView->getRenderer());

        SDL_FRect charSizeRect{
            .x = 0,
            .y = 0,
            .w = charSize,
            .h = charSize
        };

        SDL_FRect charLocRect{
            .x = playerX,
            .y = playerY,
            .w = charSize*3,
            .h = charSize*3
        };

        SDL_RenderTexture(gameView->getRenderer(), charTexture, &charSizeRect,
            &charLocRect);

        //Swap buffers and present screen
        SDL_RenderPresent(gameView->getRenderer());

    } while (gameRunning);

    std::cout << "The window is created, hit X when done..." << std::endl;

    SDL_DestroyTexture(charTexture);
    return 0;
}
/*
    auto dbManager = std::make_shared<DatabaseManager>(":memory:");//TODO change this to the actuall database file.
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);
    
    Clock::runClock(); //Start the main loop of all of this

*/
