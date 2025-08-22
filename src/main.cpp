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


//Dungeon Background
//Animations


int main(int argc, char* argv[]) {
    std::cout << "Hello World!" << std::endl;
    //Make instance.
    View* gameView = View::guiInstance().get();

    //Make player.
    Player* player = Player::playerInstance().get();
    player->attach(View::guiInstance());

    auto dbManager = std::make_shared<DatabaseManager>("DungeonDatabase.db");
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    std::vector<std::shared_ptr<NPC>> allNPCs;

    for (auto character : Bitz::getEntities()) {

        auto npc = std::dynamic_pointer_cast<NPC>(character);

        if (npc && npc->getIsActive()) {
            allNPCs.push_back(npc);

        }
    }

    //allNPCs[0]->setIsActive(false);
    Clock::runClock();




    return 0;
}


void runGame() {


}