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
//#include "include/Dungeon.h"
#include "include/Player.h"
#include "include/View.h"
#include "include/Bitz.h"
#include "include/Clock.h"

void runGame();


int main(int argc, char* argv[]) {

    std::cout << "Hello World!" << std::endl;

    View* gameView = View::guiInstance().get();

    //Loading Image
    SDL_Texture *charTexture = IMG_LoadTexture(gameView->getRenderer(),
        "assets/Kinght_Of_The_Pointer.png");
    SDL_SetTextureScaleMode(charTexture, SDL_SCALEMODE_NEAREST);

    //setup Game Data
    //float playerX {150.0}, playerY {150.0};
    //const float charSize {16.0};

    Player* player = Player::playerInstance().get();
    //player = new Player("Tom", 100, 100);

    //Game Loop
    bool gameRunning = true;
    do {
        SDL_Event gameEvent { 0 };
        gameView->handleEvent(gameEvent);

        if (!gameView->getRunning()) {
            gameRunning = false;
        }

        gameView->renderCharacter(charTexture, player);

    } while (gameRunning);

    std::cout << "The window is created, hit X when done..." << std::endl;

    SDL_DestroyTexture(charTexture);
    return 0;
}


void runGame() {
    //auto dbManager = std::make_shared<DatabaseManager>(":memory:");//TODO change this to the actuall database file.
    //Dungeon* dungeon = Dungeon::DungeonInstance();
    //dungeon->initialize(dbManager);
    Clock::runClock();

}