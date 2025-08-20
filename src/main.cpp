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

    std::cout << "Making Player..." << std::endl;
    Player* player = Player::playerInstance().get();
    player->attach(View::guiInstance());
    player->setX(1050.0);
    player->setY(1050.0);
    std::cout << Player::playerInstance()->getX()<< std::endl;
    std::cout << Player::playerInstance()->getY() << std::endl;
    std::cout << "Player made..." << std::endl;

    //Game Loop
    int directions {0};
    bool gameRunning = true;
    do {
        //std::cout << "Started loop..." << std::endl;
        SDL_Event gameEvent { 0 };
        gameView->handleEvent(gameEvent);

        if (!gameView->getRunning()) {
            gameRunning = false;
        }

        switch (directions % 4) {
            case 0:
                Player::playerInstance()->setDirection(util::SOUTH);
                break;
            case 1:
                Player::playerInstance()->setDirection(util::WEST);
                break;
            case 2:
                Player::playerInstance()->setDirection(util::NORTH);
                break;
            case 3:
                Player::playerInstance()->setDirection(util::EAST);
                break;
        }
        //Player::playerInstance()->notify(Player::PROPERTY_DIRECTION_CHANGED);
        //gameView->renderCharacter(charTexture);
        if (directions <= 10) {
            directions++;
            View::guiInstance()->Update(player, Player::PROPERTY_DIRECTION_CHANGED);
        }
        else if (directions < 20) {
            directions++;
            View::guiInstance()->Update(player, Player::PROPERTY_KILLED);
        } else {
            View::guiInstance()->Update(player, Player::PROPERTY_I_ATTACKED);
        }
            SDL_Delay(400);
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