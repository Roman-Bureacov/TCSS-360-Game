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
    /*
    SDL_Texture *charTexture = IMG_LoadTexture(gameView->getRenderer(),
        "assets/Kinght_Of_The_Pointer.png");
    SDL_SetTextureScaleMode(charTexture, SDL_SCALEMODE_NEAREST);
    */

    std::cout << "Making Player..." << std::endl;
    Player* player = Player::playerInstance().get();
    player->setX(50.0);
    player->setY(50.0);
    std::cout << player->getX() << std::endl;
    std::cout << player->getY() << std::endl;
    player->setDirection(util::SOUTH);
    std::cout << "Player made..." << std::endl;

    //Game Loop
    bool gameRunning = true;
    do {
        std::cout << "Started loop..." << std::endl;
        SDL_Event gameEvent { 0 };
        gameView->handleEvent(gameEvent);

        if (!gameView->getRunning()) {
            gameRunning = false;
        }

        gameView->Update(player, NPC::PROPERTY_DIRECTION_CHANGED);
        //gameView->renderCharacter(charTexture);

    } while (gameRunning);

    std::cout << "The window is created, hit X when done..." << std::endl;

    return 0;
}


void runGame() {
    //auto dbManager = std::make_shared<DatabaseManager>(":memory:");//TODO change this to the actuall database file.
    //Dungeon* dungeon = Dungeon::DungeonInstance();
    //dungeon->initialize(dbManager);
    Clock::runClock();

}