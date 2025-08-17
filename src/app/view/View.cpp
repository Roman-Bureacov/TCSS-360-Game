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

    // Clean up tileset texture
    if (myTilesetTexture) {
        SDL_ReleaseGPUTexture(myDevice, myTilesetTexture);
        myTilesetTexture = nullptr;
    }

    //Release Pipeline resources
    if (myGraphicsPipeline) {
        SDL_ReleaseGPUGraphicsPipeline(myDevice, myGraphicsPipeline);
    }
    if (myVertexBuffer) {
        SDL_ReleaseGPUBuffer(myDevice, myVertexBuffer);
    }
    if (myIndexBuffer) {
        SDL_ReleaseGPUBuffer(myDevice, myIndexBuffer);
    }
    if (myUniversalBuffer) {
        SDL_ReleaseGPUBuffer(myDevice, myUniversalBuffer);
    }
    if (mySampler) {
        SDL_ReleaseGPUSampler(myDevice, mySampler);
    }

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

//CLAUDE

void View::createRenderingPipeline() {

    // Query which shader formats the device supports
    const SDL_GPUShaderFormat supportedFormats = SDL_GetGPUShaderFormats(myDevice);

    // Determine which shader format to use (in order of preference)
    SDL_GPUShaderFormat chosenFormat;
    unsigned char* vertexShaderData = nullptr;
    size_t vertexShaderSize = 0;
    unsigned char* fragmentShaderData = nullptr;
    size_t fragmentShaderSize = 0;

    if (supportedFormats & SDL_GPU_SHADERFORMAT_SPIRV) {
        // Vulkan backend
        chosenFormat = SDL_GPU_SHADERFORMAT_SPIRV;
        vertexShaderData = vertexShaderSPIRV;
        vertexShaderSize = vertexShaderSPIRVSize;
        fragmentShaderData = fragmentShaderSPIRV;
        fragmentShaderSize = fragmentShaderSPIRVSize;
        std::cout << "Using SPIRV shaders (Vulkan backend)" << std::endl;
    }
    else if (supportedFormats & SDL_GPU_SHADERFORMAT_DXIL) {
        // Direct3D 12 backend
        chosenFormat = SDL_GPU_SHADERFORMAT_DXIL;
        vertexShaderData = vertexShaderDXIL;
        vertexShaderSize = vertexShaderDXILSize;
        fragmentShaderData = fragmentShaderDXIL;
        fragmentShaderSize = fragmentShaderDXILSize;
        std::cout << "Using DXIL shaders (Direct3D 12 backend)" << std::endl;
    }
    else if (supportedFormats & SDL_GPU_SHADERFORMAT_MSL) {
        // Metal backend
        chosenFormat = SDL_GPU_SHADERFORMAT_MSL;
        vertexShaderData = vertexShaderMSL;
        vertexShaderSize = vertexShaderMSLSize;
        fragmentShaderData = fragmentShaderMSL;
        fragmentShaderSize = fragmentShaderMSLSize;
        std::cout << "Using MSL shaders (Metal backend)" << std::endl;
    }
    else {
        throw SDLException("No supported shader formats available");
    }

    //TODO: Shaders

}

//END OF CLAUDE


SDL_GPUTexture* View::loadTextureFromFile(const std::string& theFilename) {


}


//CLAUDE

//This method gets the tilemap png ready to be used
void View::loadTilesetTexture(const std::string& theFilename) {
    int channels;
    unsigned char* data = stbi_load(theFilename.c_str(), &myTilesetWidth, &myTilesetHeight, &channels, STBI_rgb_alpha);

    if (!data) {
        throw SDLException("Failed to load tileset: " + theFilename);
    }

    // Create texture create info
    SDL_GPUTextureCreateInfo createInfo = {};
    createInfo.type = SDL_GPU_TEXTURETYPE_2D;
    createInfo.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    createInfo.width = myTilesetWidth;
    createInfo.height = myTilesetHeight;
    createInfo.layer_count_or_depth = 1;
    createInfo.num_levels = 1;
    createInfo.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER;

    myTilesetTexture = SDL_CreateGPUTexture(myDevice, &createInfo);
    if (!myTilesetTexture) {
        stbi_image_free(data);
        throw SDLException("Failed to create tileset GPU texture");
    }

    // Upload the image data
    SDL_GPUCommandBuffer* uploadBuffer = SDL_AcquireGPUCommandBuffer(myDevice);
    SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadBuffer);

    SDL_GPUTextureTransferInfo transferInfo = {};
    transferInfo.transfer_buffer = nullptr;
    transferInfo.offset = 0;

    SDL_GPUTextureRegion region = {};
    region.texture = myTilesetTexture;
    region.mip_level = 0;
    region.layer = 0;
    region.x = 0;
    region.y = 0;
    region.z = 0;
    region.w = myTilesetWidth;
    region.h = myTilesetHeight;
    region.d = 1;

    SDL_UploadToGPUTexture(copyPass, &transferInfo, &region, false);

    SDL_EndGPUCopyPass(copyPass);
    SDL_SubmitGPUCommandBuffer(uploadBuffer);

    stbi_image_free(data);

}


//This method maps each tile in the tilemap png to simple TileUV coords
void View::initializeTileMapping() {
    // Calculate how many tiles fit in the tileset
    // Assuming 16x16 pixel tiles
    const int tilesX = myTilesetWidth / TILE_SIZE;
    const int tilesY = myTilesetHeight / TILE_SIZE;

    std::cout << "Tileset contains " << tilesX << "x" << tilesY << " tiles" << std::endl;

    // Map tile types to their UV coordinates in the tileset
    // This assumes your tileset is organized in a grid
    // Adjust these mappings based on your actual tileset layout

    // Example mapping (you'll need to adjust these based on your tileset)
    myTileUVMap[DunText::DungeonTile::NorthWestCorner] = {0, 0};
    myTileUVMap[DunText::DungeonTile::NorthEastCorner] = {1, 0};
    myTileUVMap[DunText::DungeonTile::VerticalWall] = {2, 0};
    myTileUVMap[DunText::DungeonTile::SouthWestCorner] = {0, 1};
    myTileUVMap[DunText::DungeonTile::SouthEastCorner] = {1, 1};
    myTileUVMap[DunText::DungeonTile::HorizontalWall] = {2, 1};
    myTileUVMap[DunText::DungeonTile::Floor] = {3, 1};
    myTileUVMap[DunText::DungeonTile::HorizontalDoor] = {0, 2};
    myTileUVMap[DunText::DungeonTile::Blank] = {1, 2};
    myTileUVMap[DunText::DungeonTile::VerticalDoor] = {0, 3};

}


//This getter method returns the coords to the texture in tilemap png
TileUV View::getTileUV(const DunText::DungeonTile& theTile) {
    auto it = myTileUVMap.find(theTile);
    if (it != myTileUVMap.end()) {
        return it->second;
    }
    // Return empty/default tile if not found
    return myTileUVMap[DunText::DungeonTile::Blank];
}

//END OF CLAUDE


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