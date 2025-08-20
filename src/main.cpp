//
// Created by iwant on 7/7/2025.
//

// Example program:
// Using SDL3 to create an application window

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

#include "include/View.h"

//#include "app/model/Characters/Dummy.h"

/*
#include "include/Room.h"
#include "include/Dungeon.h"

#include "include/Bitz.h"
#include "include/Clock.h"

void runGame();
int runTest();
int showWindow();
void userPolling();
*/


void cleanup(const SDLItems &theItems);

int main(int argc, char* argv[]) {

    std::cout << "Hello World!" << std::endl;

    const View* gameView = new View();

    //Loading Image
    SDL_Texture *charTexture = IMG_LoadTexture(gameView->getRenderer(),
        "assets/Kinght_Of_The_Pointer.png");
    SDL_SetTextureScaleMode(charTexture, SDL_SCALEMODE_NEAREST);

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
        SDL_SetRenderDrawColor(gameView->getRenderer(), 5, 255, 255, 255);
        SDL_RenderClear(gameView->getRenderer());

        SDL_FRect charSizeRect{
            .x = 0,
            .y = 0,
            .w = 16,
            .h = 16
        };

        SDL_FRect charLocRect{
            .x = 0,
            .y = 0,
            .w = 96,
            .h = 96
        };

        SDL_RenderTexture(gameView->getRenderer(), charTexture, &charSizeRect,
            &charLocRect);

        //Swap buffers and present screen
        SDL_RenderPresent(gameView->getRenderer());

    }

    std::cout << "The window is created, hit X when done..." << std::endl;

    SDL_DestroyTexture(charTexture);
    return 0;
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