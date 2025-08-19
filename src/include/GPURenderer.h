//
// Created by Kyler on 8/19/2025.
//

#ifndef GPU_RENDERER_H
#define GPU_RENDERER_H

#include "Dungeon.h"
#include "AbstractCharacter.h"

class GPURenderer {
private:
    SDL_GPUDevice* device;
    SDL_GPUGraphicsPipeline* pipeline;
    SDL_GPUBuffer* uniformBuffer;
    SDL_GPUBuffer* vertexBuffer;
    SDL_GPUBuffer* indexBuffer;
    SDL_GPUSampler* sampler;

public:
    GPURenderer(SDL_GPUDevice* device);
    ~GPURenderer();

    bool initialize();
    void cleanup();
    void beginFrame(SDL_GPUCommandBuffer* commandBuffer, SDL_GPUTexture* swapchainTexture);
    void endFrame();

    // Specific render methods
    //void renderTileMap(const TileMap& tileMap, const Camera& camera);
    //void renderSprite(const Sprite& sprite, const Camera& camera);
};

#endif