
//
// Created by Kyler on 8/5/2025.
//

#ifndef VIEW_H
#define VIEW_H

#include "SDL3/SDL.h"
#include "unordered_map"
#include "RenderConfig.h"
#include "GPURenderer.h"
#include "Dungeon.h"
#include "AbstractCharacter.h";

/**
 * This Structure allows View to keep current render information for Sprites
**/
struct SpriteData {
    SDL_GPUTexture *texture;
    float x, y;
    float width, height;
    float rotation;
    bool visibleOnScreen;

    //16 by 16 is most assets in this game
    SpriteData() : texture (nullptr), x(0), y(0), width(16), height(16), rotation(0), visibleOnScreen(false) {}
};

//CLAUDE
// Structure to hold UV coordinates for tiles in the tileset
// Decides what texture will be placed in each section of the tileset
struct TileUV {
    int x, y; // Grid coordinates in the tileset (not pixel coordinates)
};

// Uniform data structure for tile rendering
struct TileUniform {
    float position[2];  // NDC position
    float scale[2];     // NDC scale
    float uvOffset[2];  // UV offset in tileset
    float uvScale[2];   // UV scale (size of one tile in UV space)
};
//END OF CLAUDE

class View : public Observer {
private:
    //SDL Window Components
    SDL_Window* myWindow;
    SDL_GPUDevice* myDevice;
    //std::shared_ptr<Observer> myDungeonSubscriber;
    bool isRunning;

    //Graphic Pipline Components
    SDL_GPUCommandBuffer* myCommandBuffer;
    SDL_GPUGraphicsPipeline* myGraphicsPipeline;
    SDL_GPUBuffer* myUniformBuffer;
    SDL_GPUBuffer* myVertexBuffer;
    SDL_GPUBuffer* myIndexBuffer;
    SDL_GPUSampler* mySampler;

    //CLAUDE

    //Tileset texture and mapping
    SDL_GPUTexture* myTilesetTexture;
    std::unordered_map<DunText::DungeonTile, TileUV> myTileUVMap;

    int myTilesetWidth{64}, myTilesetHeight{64};
    static const int TILE_SIZE = 16;
    //END OF CLAUDE

    //Map of textures?
    //SDL_GPUTexture* characterTexture;

    //Needs to track characters and dungeon


public:
    //Create View with empty window, GPU device, and declare the window isn't running (false)
    View() : myWindow(nullptr), myDevice(nullptr), isRunning(false), myCommandBuffer(nullptr),
             myGraphicsPipeline(nullptr), myUniformBuffer(nullptr), myVertexBuffer(nullptr),
             myIndexBuffer(nullptr), mySampler(nullptr), myTilesetTexture(nullptr) {}

    //Window and all GPU resources will close automatically w/ Deconstructor
    ~View() = default;

    //Create the window / GPU
    void initialize();

    //Render all sprites
    void render();

    //Handle events like closing the application
    bool handleEvents();
    void handleWindowResize(int theNewWidth, int theNewHeight);
    void handleKeyDown(const SDL_Keycode theKey);

    //Close all associated devices
    void cleanup();

    //Tells any other class that the window is open
    bool isWindowRunning() const { return isRunning; }


    //May need to implement a list to contain character information for drawSprites


    static SDL_GPUTexture* loadTextureFromFile(const std::string& theFilename);
    void loadTilesetTexture(const std::string& theFilename);
    void initializeTileMapping();
    TileUV getTileUV(const DunText::DungeonTile& theTile);
    void createRenderingPipeline();
    bool createBuffers();

    void observeDungeon(Dungeon* theDungeon);
    void unobserveDungeon(Dungeon* theDungeon);
    void observeCharacter(AbstractCharacter* theCharacter);
    void unobserveCharacter(AbstractCharacter* theCharacter);

    void Update(Subject* theChangedSubject, const std::string& thePropertyName);

    void drawRoom(SDL_GPUCommandBuffer* theCommandBuffer, SDL_GPURenderPass* theRenderPass,
        const std::vector<std::vector<DunText::DungeonTile>>& theRoomMap);
    void drawSprite(SDL_GPURenderPass* theRenderPass, SDL_GPUTexture* theTexture, float theX, float theY);
};


#endif //VIEW_H
