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

//#include "app/model/Characters/Dummy.h"
/*
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


    std::cout << "Hello World!" << std::endl;

    SDLItems theItems;

    //See if SDL Boots
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
    }



    //Make the Window
    const int width{800};
    const int height{600};
    theItems.window = SDL_CreateWindow("Game", width, height, 0);
    if (!theItems.window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        SDL_Quit();
    }

    //Create the renderer
    theItems.renderer = SDL_CreateRenderer(theItems.window, nullptr);
    if (!theItems.renderer) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL", nullptr);
        SDL_Quit();
    }

    //Loading Image

    SDL_Texture *idleTexture = IMG_LoadTexture(theItems.renderer, "assets/Kinght_Of_The_Pointer.png");

    //Game Loop
    bool gameRunning = true;
    while (gameRunning) {
        SDL_Event event { 0 };
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    gameRunning = false;
                    break;
                }
                default: break;
            }
        }

        //Perform Draw Commands
        SDL_SetRenderDrawColor(theItems.renderer, 5, 255, 255, 255);
        SDL_RenderClear(theItems.renderer);

        SDL_RenderTexture(theItems.renderer, idleTexture, nullptr, nullptr);

        //Swap buffers and present screen
        SDL_RenderPresent(theItems.renderer);

    }

    std::cout << "The window is created, hit X when done..." << std::endl;

    SDL_DestroyTexture(idleTexture);
    cleanup(theItems);
    return 0;
}


void cleanup(SDLItems &theItems) {
    SDL_DestroyWindow(theItems.window);
    SDL_DestroyRenderer(theItems.renderer);

    SDL_Quit();
}


/*
void runGame() {
    std::cout << "Running clock..." << std::endl;
    Clock::setActive(true);
    std::thread clockThread([] {
        std::cout << "Clock starting..." << std::endl;
        Clock::runClock();
        std::cout << "Clock stopping..." << std::endl;
    });


    std::cout << "Running input thread..." << std::endl;
    std::thread inputThread([] {
        std::cout << "Polling starting..." << std::endl;
        userPolling();
        std::cout << "Polling stopping..." << std::endl;
    });

    std::cout << "Awaiting further instructions..." << std::endl;
    inputThread.join();
    Clock::setActive(false);
    clockThread.join();
    std::cout << "Goodbye!" << std::endl;
}


void userPolling() {
    Dummy* d1 = new Dummy();
    Dummy* d2 = new Dummy();

    d1->setDirection(util::EAST);
    d1->setHitbox(10, 10);

    d2->setHitbox(10, 10);
    d2->setX(15);

    Bitz::registerCharacter(d1);
    Bitz::registerCharacter(d2);

    Bitz::enqueueEvent(new Event(
        1,
        []() -> void {
            std::cout << "stuff" << std::endl;
        },
        *d1
    ));

    char ch;

    while (true) {
        std::cin.get(ch);

        if (ch == '\n') continue;
        if (ch == 'q') break;

        if (ch == 'c') {
            d1->attack();
        } else {
            Event* ev;
            if (ch == 'a') {
                // do an attack
                Bitz::enqueueAttackEvent(d1);
            } else {
                // Construct an Event and enqueue it
                ev = new Event(
                    1,
                    [ch]() -> void {
                        std::cout << "Character event: " << ch << std::endl;
                    },
                    *d1
                );
                Bitz::enqueueEvent(ev);
            }

        }

    }
}
*/