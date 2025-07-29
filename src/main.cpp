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
int runTest();
int showWindow();
void userPolling();

int main(int argc, char* argv[]) {

    runGame();
    //runTest();

    return 0;
}

int runTest() {
    const AbstractCharacter me = AbstractCharacter("test", 1, 1);
    // Construct an Event and enqueue it
    Bitz::enqueueEvent( new Event(
        1,
        []() -> void {
            std::cout << "Character event: A" << std::endl;
        },
        me
    ));
    Bitz::enqueueEvent( new Event(
        1,
        []() -> void {
            std::cout << "Character event: B" << std::endl;
        },
        me
    ));
    Clock::setActive(true);
    Clock::runClock();

    return 0;
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
    const AbstractCharacter me = AbstractCharacter("test", 1, 1);
    std::cout << "I am " << me.getName() << std::endl;
    while (true) {
        char ch;
        std::cin.get(ch);

        if (ch == '\n') continue;
        if (ch == 'q') break;


        Event* ev;
        if (ch == '2') {
            // Construct an Event and enqueue it
            ev = new Event(
                2,
                [ch]() -> void {
                    std::cout << "Persistent event: " << ch << std::endl;
                },
                me
            );
        } else {
            // Construct an Event and enqueue it
            ev = new Event(
                1,
                [ch]() -> void {
                    std::cout << "Character event: " << ch << std::endl;
                },
                me
            );
        }

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