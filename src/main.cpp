//
// Created by iwant on 7/7/2025.
//

#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {

    std::cout << "Hello World!\n";
    return 1;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 Test", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    SDL_Delay(3000); // Wait 3 seconds

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
