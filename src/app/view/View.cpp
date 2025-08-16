//
// Created by Kyler on 7/1/2025.
// The GUI

#include "View.h"

#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


class SDLException final: public std::runtime_error {
    public:
        explicit SDLException(const std::string &theMessage) : std::runtime_error(theMessage + "\n" + SDL_GetError()) {
        }
};


void View::initialize() {

    std::cout << "Opening Game Window..." << std::endl;

    // Initialize SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw SDLException("Failed to initialize SDL");
    }

    //Assigns window with specified dimensions for the player to view
    myWindow = SDL_CreateWindow("Dungeon Game", 800, 600, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (!myWindow) {
        throw SDLException("Failed to create window");
    }

    //Create device directly with SLD_GPU (unique to SLD3).
    //Runs off Direct12, Vulkan, and Metal
    //Throws exception if fails to create device
    myDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL,
        true, nullptr);
    if (!myDevice) {
        throw SDLException("Failed to create GPU device");
    }

    //Claim Window for GPU device
    if (!SDL_ClaimWindowForGPUDevice(myDevice, myWindow)) {
        throw SDLException("Failed to claim window for GPU device");
    }

    createRenderingPipeline();

    SDL_ShowWindow(myWindow);
    isRunning = true;
}


void View::render() {

    SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(myDevice);
    if (!commandBuffer) {
        throw SDLException{"Failed to acquire GPU command buffer"};
    }

    SDL_GPUTexture* swapchainTexture = nullptr;
    Uint32 swapchainWidth, swapchainHeight;
    if (!SDL_AcquireGPUSwapchainTexture(commandBuffer, myWindow, &swapchainTexture, &swapchainWidth, &swapchainHeight)) {
        throw SDLException{"Failed to acquire swapchain texture"};
    }

    if (!swapchainTexture) {
        return; // Try again next frame
    }

    SDL_GPUColorTargetInfo colorTarget = {};
    colorTarget.texture = swapchainTexture;
    colorTarget.clear_color = {1.0f, 1.0f, 1.0f, 1.0f}; // White background
    colorTarget.load_op = SDL_GPU_LOADOP_CLEAR;
    colorTarget.store_op = SDL_GPU_STOREOP_STORE;

    // Begin render pass
    SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(
        commandBuffer,
        &colorTarget, 1,
        nullptr  // No depth buffer for now
    );

    //We'll place our sprite drawing method(s) here

    // End render pass and submit
    SDL_EndGPURenderPass(renderPass);

    if (!SDL_SubmitGPUCommandBuffer(commandBuffer))
        throw SDLException{"Failed to submit GPU command buffer"};
}


bool View::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                isRunning = false;
                return false;


            default:
                break;
        }
    }
    return true;
}


void View::cleanup() {
    std::cout << "Closing Window" << std::endl;

    //Free the window and GPU
    SDL_ReleaseWindowFromGPUDevice(myDevice, myWindow);

    //Close and destroy GPU
    SDL_DestroyGPUDevice(myDevice);

    // Close and destroy the window
    SDL_DestroyWindow(myWindow);

    // Clean up
    SDL_Quit();

    std::cout << "Window Destroyed" << std::endl;
}


void View::createRenderingPipeline() {


    //TODO: Shaders

}


void View::observeDungeon(Dungeon* theDungeon) {
    if (!theDungeon) throw SDLException{"Dungeon is null"};

    theDungeon->attach(std::unique_ptr<Observer>(this));

}


void View::unobserveDungeon(Dungeon* theDungeon) {
    if (!theDungeon) throw SDLException{"Failed to null Dungeon"};

    theDungeon->detach(std::unique_ptr<Observer>(this));

}


void View::observeCharacter(AbstractCharacter* theCharacter) {
    if (!theCharacter) throw SDLException{"Failed to observe character"};

    theCharacter->attach(std::unique_ptr<Observer>(this));

    //May need to include data structure that holds active chars
}


void View::unobserveCharacter(AbstractCharacter* theCharacter) {
    if (!theCharacter) throw SDLException{"Failed to unobserve character"};

    theCharacter->detach(std::unique_ptr<Observer>(this));

    //May need to remove from data structure that holds active chars
}


void View::Update(Subject* theChangedSubject, const std::string& thePropertyName) {

}


void View::drawRoom() {

}


void View::drawSprite(SDL_GPURenderPass* theRenderPass, SDL_GPUTexture* theTexture, float theX, float theY) {

}