//
// Created by Kyler on 7/1/2025.
// The GUI

#include "../../include/View.h"

#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

class SDLException final: public std::runtime_error {
    public:
        explicit SDLException(const std::string &message) : std::runtime_error(message + "\n" + SDL_GetError()) {
        }
};

void View::initialize() {

    std::cout << "Opening Game Window..." << std::endl;

    // Initialize SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw SDLException("Failed to initialize SDL");
    }

    //Assigns window with specified dimensions for the player to view
    window = SDL_CreateWindow("Dungeon Game", 800, 600, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if (!window) {
        throw SDLException("Failed to create window");
    }

    //Create device directly with SLD_GPU (unique to SLD3).
    //Runs off Direct12, Vulkan, and Metal
    //Throws exception if fails to create device
    device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL,
        true, nullptr);
    if (!device) {
        throw SDLException("Failed to create GPU device");
    }

    //Claim Window for GPU device
    if (!SDL_ClaimWindowForGPUDevice(device, window)) {
        throw SDLException("Failed to claim window for GPU device");
    }

    SDL_ShowWindow(window);
    isRunning = true;
}

void View::render() {

    SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);
    if (!commandBuffer) {
        throw SDLException("Failed to acquire GPU command buffer");
    }

    SDL_GPUTexture* swapchainTexture = nullptr;
    Uint32 swapchainWidth, swapchainHeight;
    if (!SDL_AcquireGPUSwapchainTexture(commandBuffer, window, &swapchainTexture, &swapchainWidth, &swapchainHeight)) {
        throw SDLException("Failed to acquire swapchain texture");
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
    SDL_SubmitGPUCommandBuffer(commandBuffer);
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
    SDL_ReleaseWindowFromGPUDevice(device, window);

    //Close and destroy GPU
    SDL_DestroyGPUDevice(device);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    std::cout << "Window Destroyed" << std::endl;
}
