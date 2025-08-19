//
// Created by Kyler on 8/19/2025.
//

#pragma once

struct windowConfigStructure {
    int screenWidth{800};
    int screenHeight{600};
    const char* title = "Dungeon Game!";
    bool resizable = true;
    bool vsync = true;
};

struct RenderConfig {
    //Static Constants for Color and PNG Tile Sizes (In Bytes)
    static constexpr int TILE_SIZE = 16;
    static constexpr int BYTES_PER_PIXEL = 4; // RGBA
    static constexpr float CLEAR_COLOR_R = 0.1f;
    static constexpr float CLEAR_COLOR_G = 1.0f;
    static constexpr float CLEAR_COLOR_B = 1.0f;
    static constexpr float CLEAR_COLOR_A = 1.0f;

    //Shader Pathways
    struct ShaderPaths {
        const char* dxilVertex = "shaders/dxil/shader.vert.dxil";
        const char* dxilFragment = "shaders/dxil/shader.frag.dxil";
        const char* spvVertex = "shaders/spv/shader.vert.spv";
        const char* spvFragment = "shaders/spv/shader.frag.spv";
    };

    static const ShaderPaths SHADERS;

    // Asset paths
    struct AssetPaths {
        const char* tilesetTexture = "assets/Tiling_dungeon_Tile_Set.png";
        const char* goblinTileTexture = "assets/Goblin_Of_Null.png";
        const char* skeletonTileTexture = "assets/Skelleton_Of_Null.png";
        const char* TimTileTexture = "assets/Dark_Lord_Tom.png";
        const char* playerTileTexture = "assets/Knight_Of_The_Pointer.png";

        const char* music = "assets/Null Us All.mp3"; //Maybe?
    };

    static const AssetPaths ASSETS;

};
