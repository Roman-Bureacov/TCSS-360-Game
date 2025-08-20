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

void runGame();
int runTest();
int showWindow();
void userPolling();
*/

struct SDLItems {
    SDL_Window* window;
    SDL_Renderer* renderer;

};

void cleanup(SDLItems &theItems);

int main(int argc, char* argv[]) {

    auto dbManager = std::make_shared<DatabaseManager>(":memory:");//TODO change this to the actuall database file.
    Dungeon* dungeon = Dungeon::DungeonInstance();
    dungeon->initialize(dbManager);

    Bitz::registerCharacter(d1);
    Bitz::registerCharacter(d2);

    Clock::runClock(); //Start the main loop of all of this

}
