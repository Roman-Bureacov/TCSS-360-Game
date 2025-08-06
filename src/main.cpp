//
// Created by iwant on 7/7/2025.
//

// Example program:
// Using SDL3 to create an application window

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <thread>

#include "app/model/Characters/Dummy.h"

#include "app/view/View.h"

#include "include/Bitz.h"
#include "include/Clock.h"

void runGame();
int runTest();
int showWindow();
void userPolling();

int main(int argc, char* argv[]) {

    std::cout << "Hello Console, we're opening window..." << std::endl;

    //VIEW TEST BEGINS
    //Create the view
    View userView;
    //Initialize (open) Window
    userView.initialize();

    std::cout << "The window is created, hit X when done..." << std::endl;

    //Main should be creating the controller and controller will handle view and model

    //While window is open and running...
    while (userView.isWindowRunning()) {
        //Check if window has been closed
        if (!userView.handleEvents()) {
            break;
        }

        userView.render();

    }

    //Closes Window and closes all associated resources
    userView.cleanup();
    //VIEW TEST ENDS

    runGame();

    return 0;
}

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
    char ch;
    Dummy dumb;

    //std::cout << "I am " << dumb.getName() << std::endl;

    std::cout << "Start Loop" << std::endl;
    while (true) {
        std::cin.get(ch);

        if (ch == '\n') continue;
        if (ch == 'q') break;

        if (ch == 'c') {
            dumb.attack();
        } else {
            Event* ev;
            if (ch == '2') {
                // Construct an Event and enqueue it
                ev = new Event(
                    2,
                    [ch]() -> void {
                        std::cout << "Persistent event: " << ch << std::endl;
                    },
                    dumb
                );
            } else {
                // Construct an Event and enqueue it
                ev = new Event(
                    1,
                    [ch]() -> void {
                        std::cout << "Character event: " << ch << std::endl;
                    },
                    dumb
                );
            }

            Bitz::enqueueEvent(ev);
        }

    }
}
