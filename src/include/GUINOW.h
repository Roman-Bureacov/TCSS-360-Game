//
// Created by riley on 8/19/25.
//

#ifndef GUINOW_H
#define GUINOW_H

#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_image.h>

#include "ObserverPattern.h"

class GUINOW : public Observer {

public:
    GUINOW();


    ~GUINOW();
    bool init();

    void Update(Subject* theChangedSubject,
        const std::string& thePropertyName) override;

    void draw();

private:

    void drawRoom();
    void drawCharacters();

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    SDL_Renderer* renderer;
    std::vector<std::string> sprites;

    static constexpr  int xDim = 1500;
    static constexpr int yDim = 1500;




};



#endif //GUINOW_H
