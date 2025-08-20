//
// Created by riley on 8/19/25.
//

#include "../../include/GUINOW.h"

GUINOW::GUINOW() {

    bool success = true;
    // Initialize SDL video subsystem
    if( SDL_Init( SDL_INIT_VIDEO ) == false )  {
        SDL_Log( "SDL could not initialize! SDL error: %s\n", SDL_GetError() );
        success = false;
    }

    if( window = SDL_CreateWindow( "Sloppy dungeon", xDim, yDim, 0 )
        ; window == nullptr ) {
        SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
        success = false;
    }

    //get the screen surface.
    screenSurface = SDL_GetWindowSurface( window );

    //Creates the renderer.
    renderer = SDL_CreateRenderer(window, NULL);


}



GUINOW::~GUINOW() {
}

void GUINOW::Update(Subject *theChangedSubject, const std::string &thePropertyName) {
}

void GUINOW::draw() {
}

void GUINOW::drawRoom() {
}

void GUINOW::drawCharacters() {
}
