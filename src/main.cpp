//
// Created by iwant on 7/7/2025.
//

// Example program:
// Using SDL3 to create an application window

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <thread>

#include "eng/Bitz.h"
#include "eng/Clock.h"

int runGame();
int showWindow();
void userPolling();

int main(int argc, char* argv[]) {

    return std::max(runGame(), 0);
}

int runGame() {
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
    return 69;
}

void userPolling() {
    std::string cmd;
    while (true) {
        char ch;
        std::cin.get(ch);

        if (ch == '\n') continue;
        if (ch == 'q') break;

        // Construct an Event and enqueue it
        Event* ev = new Event(
            1,
            [ch]() -> void {
                std::cout << "Character event: " << ch << std::endl;
            },
            AbstractCharacter()
        );

        Bitz::enqueueEvent(ev);
    }
}


/**
 * SDL example to show that it's running
 */
int showWindow() {
    std::cout << "Starting..." << std::endl;

    SDL_Window *window;                    // Declare a pointer
    bool done = false;

    std::cout << "Getting a window..." << std::endl;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    std::cout << "Creating window..." << std::endl;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    std::cout << "Does this window exist?" << std::endl;

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        std::cout << "did not create window" << std::endl;
        return 1;
    }

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        // Do game logic, present a frame, etc.
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}