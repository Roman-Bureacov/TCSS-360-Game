//
// Created by Kyler on 7/1/2025.
// The GUI

#include "../../include/View.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb_image.h"

class SDLException final: public std::runtime_error {
    public:
        explicit SDLException(const std::string &theMessage) : std::runtime_error(theMessage + "\n" + SDL_GetError()) {
        }
};

const std::vector<std::vector<DunText::DungeonTile>> testRoom (10,
        std::vector<DunText::DungeonTile>(10, DunText::DungeonTile::Floor));

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
    //Runs off Direct12, or Vulkan
    //Throws exception if fails to create device
    myDevice = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_SPIRV,
        true, nullptr);
    if (!myDevice) {
        throw SDLException("Failed to create GPU device");
    }

    //Claim Window for GPU device
    if (!SDL_ClaimWindowForGPUDevice(myDevice, myWindow)) {
        throw SDLException("Failed to claim window for GPU device");
    }

    std::cout << "Creating pipeline..." << std::endl;
    createRenderingPipeline();

    std::cout << "Load Tilemap Texture..." << std::endl;
    //TODO: Make file below a constant?
    loadTilesetTexture("assets/Tiling_dungeon_Tile_Set.png");
    std::cout << "Load Mapping..." << std::endl;
    initializeTileMapping();

    SDL_ShowWindow(myWindow);
    isRunning = true;
}


void View::render() {
    std::cout << "Rendering Game Window..." << std::endl;

    myCommandBuffer = SDL_AcquireGPUCommandBuffer(myDevice);
    if (!myCommandBuffer) {
        throw SDLException{"Failed to acquire GPU command buffer"};
    }

    if (!isWindowRunning())
        SDL_CancelGPUCommandBuffer(myCommandBuffer);

    SDL_GPUTexture* swapchainTexture = nullptr;
    Uint32 swapchainWidth, swapchainHeight;
    if (!SDL_AcquireGPUSwapchainTexture(myCommandBuffer, myWindow, &swapchainTexture, &swapchainWidth, &swapchainHeight)) {
        throw SDLException{"Failed to acquire swapchain texture"};
    }
    printf("Created Swapchain: %p\n", static_cast<void *>(swapchainTexture));

    if (!swapchainTexture) {
        return; // Try again next frame
    }

    SDL_GPUColorTargetInfo colorTarget = {};
    colorTarget.texture = swapchainTexture;
    colorTarget.clear_color = {0.1f, 1.0f, 1.0f, 1.0f}; // Cyan background
    colorTarget.load_op = SDL_GPU_LOADOP_CLEAR;
    colorTarget.store_op = SDL_GPU_STOREOP_STORE;

    // Begin render pass
    SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(
        myCommandBuffer,
        &colorTarget, 1,
        nullptr  // No depth buffer for now
    );
    printf("Created Renderpass: %p\n", static_cast<void *>(renderPass));


    //We'll place our sprite drawing method(s) here
    std::cout << "Drawing Room" << std::endl;
    drawRoom(myCommandBuffer, renderPass, testRoom);

    // End render pass and submit
    SDL_EndGPURenderPass(renderPass);
    printf("Destory renderpass: %p\n", static_cast<void *>(renderPass));


    if (!SDL_SubmitGPUCommandBuffer(myCommandBuffer))
        throw SDLException{"Failed to submit GPU command buffer"};


}


bool View::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                isRunning = false;
                cleanup();
                return false;

            case SDL_EVENT_WINDOW_RESIZED:
                handleWindowResize(event.window.data1, event.window.data2);
                break;

            case SDL_EVENT_KEY_DOWN:
                //handleKeyDown(event.key.key);
                break;

            default:
                break;
        }
    }
    return true;
}


void View::handleWindowResize(const int theNewWidth, const int theNewHeight) {
    //myCamera.updateViewport(theNewWidth, theNewHeight);
    // Possibly update any UI elements that depend on window size
}


void View::handleKeyDown(const SDL_Keycode theKey) {
    switch (theKey) {
        case SDLK_ESCAPE:
            isRunning = false;
            cleanup();
            break;
        case SDLK_F11:
            SDL_SetWindowFullscreen(myWindow, true);
            break;
        default:
            break;
    }
}


void View::cleanup() {
    std::cout << "Closing Window" << std::endl;

    // Stop any rendering loop first (if you have a separate render thread,
    // ensure it has been told to stop and joined)
    isRunning = false;

    if (myDevice)
        SDL_WaitForGPUIdle(myDevice);

    if (myCommandBuffer) {
        myCommandBuffer = nullptr;
    }

    if (myGraphicsPipeline) {
        SDL_ReleaseGPUGraphicsPipeline(myDevice, myGraphicsPipeline);
        myGraphicsPipeline = nullptr;
    }

    if (myTilesetTexture) {
        SDL_ReleaseGPUTexture(myDevice, myTilesetTexture);
        myTilesetTexture = nullptr;
    }

    if (myUniformBuffer) {
        SDL_ReleaseGPUBuffer(myDevice, myUniformBuffer);
        printf("Releasing buffer: %p\n", static_cast<void *>(myUniformBuffer));
        myUniformBuffer = nullptr;
    }
    if (myVertexBuffer) {
        SDL_ReleaseGPUBuffer(myDevice, myVertexBuffer);
        printf("Releasing buffer: %p\n", static_cast<void *>(myVertexBuffer));

        myVertexBuffer = nullptr;
    }
    if (myIndexBuffer) {
        SDL_ReleaseGPUBuffer(myDevice, myIndexBuffer);
        printf("Releasing buffer: %p\n", static_cast<void *>(myIndexBuffer));

        myIndexBuffer = nullptr;
    }

    if (mySampler) {
        SDL_ReleaseGPUSampler(myDevice, mySampler);
        mySampler = nullptr;
    }

    // If we have any outstanding transfer buffers, fences, or command buffers we must
    // ensure they are finished / canceled on the thread that acquired them.
    // (SDL_WaitForGPUIdle above helps for submitted work.)

    //Free the window and GPU
    SDL_ReleaseWindowFromGPUDevice(myDevice, myWindow);

    // Close and destroy the window
    SDL_DestroyWindow(myWindow);
    myWindow = nullptr;

    //Close and destroy GPU
    SDL_DestroyGPUDevice(myDevice);
    myDevice = nullptr;

    // Clean up
    SDL_Quit();

    std::cout << "Window Destroyed" << std::endl;
}

//CLAUDE

void View::createRenderingPipeline() {
    // Get the GPU driver to determine which shader format to use
    const std::string driverFormat = SDL_GetGPUDeviceDriver(myDevice);
    std::cout << "Driver Format... " << driverFormat << std::endl;
    SDL_GPUShaderFormat chosenFormat;

    const char* vertexShaderPath = nullptr;
    const char* fragmentShaderPath = nullptr;

    // Choose shader files based on GPU driver
    if (driverFormat == "direct3d11" || driverFormat == "direct3d12") {
        vertexShaderPath = "shaders/dxil/shader.vert.dxil";
        fragmentShaderPath = "shaders/dxil/shader.frag.dxil";
        chosenFormat = SDL_GPU_SHADERFORMAT_DXIL;
    }
    else if (driverFormat == "vulkan") {
        vertexShaderPath = "shaders/spv/shader.vert.spv";
        fragmentShaderPath = "shaders/spv/shader.frag.spv";
        chosenFormat = SDL_GPU_SHADERFORMAT_SPIRV;
    }
    else
        throw SDLException{"Error: Unsupported GPU driver"};

    std::cout << "Passed the Driver Check..." << std::endl;

    std::cout << "Vertex Shader Path... " << vertexShaderPath << std::endl;
    std::cout << "Fragment Shader Path... " << fragmentShaderPath << std::endl;

    // Load shader files
    SDL_IOStream* vertexShaderFile = SDL_IOFromFile(vertexShaderPath, "rb");
    SDL_IOStream* fragmentShaderFile = SDL_IOFromFile(fragmentShaderPath, "rb");
    if (!vertexShaderFile || !fragmentShaderFile) {
        SDL_Log("Error: Failed to load shader files");
        if (vertexShaderFile) SDL_CloseIO(vertexShaderFile);
        if (fragmentShaderFile) SDL_CloseIO(fragmentShaderFile);
        return;
    }

    std::cout << "Shader File Recognised Check" << std::endl;

    // Get shader file sizes
    Sint64 vertexSize = SDL_GetIOSize(vertexShaderFile);
    Sint64 fragmentSize = SDL_GetIOSize(fragmentShaderFile);
    if (vertexSize <= 0 || fragmentSize <= 0) {
        SDL_CloseIO(vertexShaderFile);
        SDL_CloseIO(fragmentShaderFile);
        throw SDLException{"Error: Invalid shader file sizes"};
    }

    std::cout << "Got the file sizes Check" << std::endl;

    // Allocate memory for shader bytecode
    void* vertexCode = malloc(vertexSize);
    void* fragmentCode = malloc(fragmentSize);
    if (!vertexCode || !fragmentCode) {
        free(vertexCode);
        free(fragmentCode);
        SDL_CloseIO(vertexShaderFile);
        SDL_CloseIO(fragmentShaderFile);
        throw SDLException{"Error: Failed to allocate memory for shaders"};
    }

    std::cout << "Memory Space Allocated Check" << std::endl;

    // Read shader bytecode
    size_t vertexBytesRead = SDL_ReadIO(vertexShaderFile, vertexCode, vertexSize);
    size_t fragmentBytesRead = SDL_ReadIO(fragmentShaderFile, fragmentCode, fragmentSize);

    std::cout << "Shaders Read Check" << std::endl;

    SDL_CloseIO(vertexShaderFile);
    SDL_CloseIO(fragmentShaderFile);

    std::cout << "Files Closed Check" << std::endl;

    if (vertexBytesRead != vertexSize || fragmentBytesRead != fragmentSize) {
        free(vertexCode);
        free(fragmentCode);
        throw SDLException{"Error: Failed to read complete shader files"};
    }

    std::cout << "Shaders were completely read Check" << std::endl;

    //Let's make some shaders!
    SDL_GPUShader* vertexShader = nullptr;
    SDL_GPUShader* fragmentShader = nullptr;

    // Create vertex shader
    SDL_GPUShaderCreateInfo vertexShaderInfo = {};
    vertexShaderInfo.code_size = vertexSize;
    vertexShaderInfo.code = static_cast<Uint8 *>(vertexCode);
    vertexShaderInfo.entrypoint = "main";
    vertexShaderInfo.format = chosenFormat;
    vertexShaderInfo.stage = SDL_GPU_SHADERSTAGE_VERTEX;
    vertexShaderInfo.num_uniform_buffers = 0; // For projection matrix
    vertexShaderInfo.num_samplers = 0; // For texture sampling

    std::cout << "Vertex Staged....." << std::endl;

    vertexShader = SDL_CreateGPUShader(myDevice, &vertexShaderInfo);
    if (!vertexShader) {
        throw SDLException{"Failed to create vertex shader"};
    }

    std::cout << "Vertex Made Check" << std::endl;

    //Create fragment shader
    SDL_GPUShaderCreateInfo fragmentShaderInfo = {};
    fragmentShaderInfo.code_size = fragmentSize;
    fragmentShaderInfo.code = static_cast<Uint8 *>(fragmentCode);
    fragmentShaderInfo.entrypoint = "main";
    fragmentShaderInfo.format = chosenFormat;
    fragmentShaderInfo.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    fragmentShaderInfo.num_uniform_buffers = 0;
    fragmentShaderInfo.num_samplers = 0;

    std::cout << "Fragment Staged....." << std::endl;

    /**
    printf("[VS] ubo=%u samplers=%u size=%llu\n", vertexShaderInfo.num_uniform_buffers, vertexShaderInfo.num_samplers, vertexShaderInfo.code_size);
    printf("[FS] ubo=%u samplers=%u size=%llu\n", fragmentShaderInfo.num_uniform_buffers, fragmentShaderInfo.num_samplers, fragmentShaderInfo.code_size);
    printf("Format=%d (expect %d for Vulkan)\n", static_cast<int>(chosenFormat), static_cast<int>(SDL_GPU_SHADERFORMAT_SPIRV));
    */
    fragmentShader = SDL_CreateGPUShader(myDevice, &fragmentShaderInfo);
    if (!fragmentShader) {
        SDL_ReleaseGPUShader(myDevice, vertexShader);
        throw SDLException{"Failed to create fragment shader"};
    }

    std::cout << "Fragment Made Check" << std::endl;

    // Free shader bytecode memory
    free(vertexCode);
    free(fragmentCode);

    std::cout << "Shaders Bytecode Freed Check" << std::endl;

    // Define vertex input layout for sprites (position + texture coordinates + color)
    SDL_GPUVertexAttribute vertexAttributes[3]{};
    // Position attribute (vec3) (3 floats = 12 bytes)
    vertexAttributes[0].location = 0;
    vertexAttributes[0].buffer_slot = 0;
    vertexAttributes[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
    vertexAttributes[0].offset = 0;
    // Texture coordinate attribute (vec2) (2 floats = 8 bytes)
    vertexAttributes[1].location = 1;
    vertexAttributes[1].buffer_slot = 0;
    vertexAttributes[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
    vertexAttributes[1].offset = 12;
    // Color (vec3) (3 floats = 12 bytes)
    vertexAttributes[2].location = 2;
    vertexAttributes[2].format   = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3; // aColor
    vertexAttributes[2].offset   = 20;
    vertexAttributes[2].buffer_slot = 0;

    SDL_GPUVertexBufferDescription vertexBuffer = {};
    vertexBuffer.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX;
    vertexBuffer.slot = 0;
    vertexBuffer.pitch = 32; //sizeof(vertexAttributes)

    SDL_GPUVertexInputState vertexInputState = {};
    vertexInputState.vertex_buffer_descriptions = &vertexBuffer;
    vertexInputState.num_vertex_buffers = 1;
    vertexInputState.vertex_attributes = vertexAttributes;
    vertexInputState.num_vertex_attributes = 3;


    // Color target with alpha blending
    SDL_GPUColorTargetDescription colorTarget = {};
    colorTarget.format = SDL_GetGPUSwapchainTextureFormat(myDevice, myWindow);
    colorTarget.blend_state.enable_blend = true;
    colorTarget.blend_state.enable_color_write_mask = true;
    colorTarget.blend_state.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA;
    colorTarget.blend_state.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    colorTarget.blend_state.color_blend_op = SDL_GPU_BLENDOP_ADD;
    colorTarget.blend_state.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE;
    colorTarget.blend_state.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ZERO;
    colorTarget.blend_state.alpha_blend_op = SDL_GPU_BLENDOP_ADD;
    colorTarget.blend_state.color_write_mask = SDL_GPU_COLORCOMPONENT_R | SDL_GPU_COLORCOMPONENT_G |
                                           SDL_GPU_COLORCOMPONENT_B | SDL_GPU_COLORCOMPONENT_A;

    SDL_GPURasterizerState rasterizerState = {};
    rasterizerState.fill_mode = SDL_GPU_FILLMODE_FILL;
    rasterizerState.cull_mode = SDL_GPU_CULLMODE_NONE;
    rasterizerState.front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE;
    rasterizerState.depth_bias_constant_factor = 0.0f;
    rasterizerState.depth_bias_clamp = 0.0f;
    rasterizerState.depth_bias_slope_factor = 0.0f;
    rasterizerState.enable_depth_bias = false;
    rasterizerState.enable_depth_clip = false;

    // Multisample state (no multisampling for now)
    SDL_GPUMultisampleState multisampleState = {};
    multisampleState.sample_count = SDL_GPU_SAMPLECOUNT_1;
    multisampleState.sample_mask = 0x00000000;
    //multisampleState.sample_mask = 0xFFFFFFFF;
    multisampleState.enable_mask = false;


    std::cout << "Helper Structs made Check... About to create Pipeline" << std::endl;

    // Create graphics pipeline
    SDL_GPUGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.vertex_shader = vertexShader;
    pipelineInfo.fragment_shader = fragmentShader;
    pipelineInfo.vertex_input_state = vertexInputState;
    pipelineInfo.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
    pipelineInfo.rasterizer_state = rasterizerState;
    pipelineInfo.multisample_state = multisampleState;
    pipelineInfo.target_info.num_color_targets = 1;
    pipelineInfo.target_info.color_target_descriptions = &colorTarget;
    pipelineInfo.target_info.depth_stencil_format = SDL_GPU_TEXTUREFORMAT_INVALID; // No depth buffer
    pipelineInfo.target_info.has_depth_stencil_target = false;

    std::cout << "Pipeline Staged....." << std::endl;

    myGraphicsPipeline = SDL_CreateGPUGraphicsPipeline(myDevice, &pipelineInfo);
    if (!myGraphicsPipeline) {
        SDL_ReleaseGPUShader(myDevice, vertexShader);
        SDL_ReleaseGPUShader(myDevice, fragmentShader);
        throw SDLException{"Failed to create graphics pipeline"};
    }

    std::cout << "Pipeline Created Check" << std::endl;

    // Create sampler for texture sampling
    SDL_GPUSamplerCreateInfo samplerInfo = {};
    samplerInfo.min_filter = SDL_GPU_FILTER_NEAREST; // Pixel-perfect for retro look
    samplerInfo.mag_filter = SDL_GPU_FILTER_NEAREST;
    samplerInfo.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST;
    samplerInfo.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    samplerInfo.mip_lod_bias = 0.0f;
    samplerInfo.enable_anisotropy = false;
    samplerInfo.max_anisotropy = 1.0f;
    samplerInfo.enable_compare = false;
    samplerInfo.compare_op = SDL_GPU_COMPAREOP_ALWAYS;
    samplerInfo.min_lod = 0.0f;
    samplerInfo.max_lod = 1000.0f;

    mySampler = SDL_CreateGPUSampler(myDevice, &samplerInfo);
    if (!mySampler) {
        SDL_ReleaseGPUGraphicsPipeline(myDevice, myGraphicsPipeline);
        SDL_ReleaseGPUShader(myDevice, vertexShader);
        SDL_ReleaseGPUShader(myDevice, fragmentShader);
        throw SDLException{"Failed to create sampler"};
    }


    // Clean up shaders (pipeline retains references)
    SDL_ReleaseGPUShader(myDevice, vertexShader);
    SDL_ReleaseGPUShader(myDevice, fragmentShader);


    //Create the Buffers (in separate method for compartmentalization)
    //If failed to create Buffers, call cleanup

    //Problem?
    if (!createBuffers()) {
        cleanup();
        throw SDLException{"Failed to create buffers"};
    }

    std::cout << "Rendering pipeline created successfully!" << std::endl;

}


bool View::createBuffers() {
    std::cout << "Creating buffers..." << std::endl;

    // Create uniform buffer for projection matrix
    SDL_GPUBufferCreateInfo uniformBufferInfo = {};
    uniformBufferInfo.usage = SDL_GPU_BUFFERUSAGE_GRAPHICS_STORAGE_READ;
    uniformBufferInfo.size = sizeof(float) * 16; // 4x4 matrix

    myUniformBuffer = SDL_CreateGPUBuffer(myDevice, &uniformBufferInfo);

    // Create vertex buffer for sprite quad vertices
    // Each vertex has: position (2 floats) + texcoord (2 floats) = 4 floats
    const float quadVertices[] = {
        // Position     // TexCoord
        -0.5f, -0.5f,   0.0f, 1.0f,  // Bottom-left
         0.5f, -0.5f,   1.0f, 1.0f,  // Bottom-right
         0.5f,  0.5f,   1.0f, 0.0f,  // Top-right
        -0.5f,  0.5f,   0.0f, 0.0f   // Top-left
    };

    SDL_GPUBufferCreateInfo vertexBufferInfo = {};
    vertexBufferInfo.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
    vertexBufferInfo.size = sizeof(quadVertices);
    myVertexBuffer = SDL_CreateGPUBuffer(myDevice, &vertexBufferInfo);

    SDL_GPUTransferBufferCreateInfo vertexBufferUploadInfo = {};
    vertexBufferUploadInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
    vertexBufferUploadInfo.size = sizeof(quadVertices);

    // Upload vertex data to buffer
    SDL_GPUTransferBuffer* vertexUploadBuffer = SDL_CreateGPUTransferBuffer(myDevice,
        &vertexBufferUploadInfo);

    void* mappedData = SDL_MapGPUTransferBuffer(myDevice, vertexUploadBuffer, false);
    memcpy(mappedData, quadVertices, sizeof(quadVertices));
    SDL_UnmapGPUTransferBuffer(myDevice, vertexUploadBuffer);

    // Create index buffer for quad (2 triangles)
    uint16_t quadIndices[] = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };

    SDL_GPUBufferCreateInfo indexBufferInfo = {};
    indexBufferInfo.usage = SDL_GPU_BUFFERUSAGE_INDEX;
    indexBufferInfo.size = sizeof(quadIndices);
    myIndexBuffer = SDL_CreateGPUBuffer(myDevice, &indexBufferInfo);

    SDL_GPUTransferBufferCreateInfo indexBufferUploadInfo = {};
    indexBufferUploadInfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
    indexBufferUploadInfo.size = sizeof(quadIndices);

    // Upload index data
    SDL_GPUTransferBuffer* indexUploadBuffer = SDL_CreateGPUTransferBuffer(myDevice,
        &indexBufferUploadInfo);

    void* indexMappedData = SDL_MapGPUTransferBuffer(myDevice, indexUploadBuffer, false);
    memcpy(indexMappedData, quadIndices, sizeof(quadIndices));
    SDL_UnmapGPUTransferBuffer(myDevice, indexUploadBuffer);

    if (!myUniformBuffer || !myVertexBuffer || !myIndexBuffer) {
        SDL_ReleaseGPUTransferBuffer(myDevice, vertexUploadBuffer);
        SDL_ReleaseGPUTransferBuffer(myDevice, indexUploadBuffer);
        SDL_ReleaseGPUBuffer(myDevice, myIndexBuffer);
        SDL_ReleaseGPUBuffer(myDevice, myVertexBuffer);
        SDL_ReleaseGPUBuffer(myDevice, myUniformBuffer);
        return false;
    }

    // Copy data to GPU buffers using copy pass
    SDL_GPUCommandBuffer* uploadCommandBuffer = SDL_AcquireGPUCommandBuffer(myDevice);
    SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadCommandBuffer);

    SDL_GPUTransferBufferLocation vertexSource = {};
    vertexSource.transfer_buffer = vertexUploadBuffer;
    vertexSource.offset = 0;

    SDL_GPUBufferRegion vertexDestination = {};
    vertexDestination.buffer = myVertexBuffer;
    vertexDestination.offset = 0;
    vertexDestination.size = sizeof(quadVertices);

    SDL_UploadToGPUBuffer(copyPass, &vertexSource, &vertexDestination, false);

    SDL_GPUTransferBufferLocation indexSource = {};
    indexSource.transfer_buffer = indexUploadBuffer;
    indexSource.offset = 0;

    SDL_GPUBufferRegion indexDestination = {};
    indexDestination.buffer = myIndexBuffer;
    indexDestination.offset = 0;
    indexDestination.size = sizeof(quadIndices);

    SDL_UploadToGPUBuffer(copyPass, &indexSource, &indexDestination, false);

    SDL_EndGPUCopyPass(copyPass);
    SDL_SubmitGPUCommandBuffer(uploadCommandBuffer);

    // Wait for upload to complete before cleaning up transfer buffers
    SDL_WaitForGPUIdle(myDevice);
    SDL_ReleaseGPUTransferBuffer(myDevice, vertexUploadBuffer);
    printf("Releasing buffer: %p\n", static_cast<void *>(vertexUploadBuffer));

    SDL_ReleaseGPUTransferBuffer(myDevice, indexUploadBuffer);
    printf("Releasing buffer: %p\n", static_cast<void *>(indexUploadBuffer));


    std::cout << "Successfully made Buffers!" << std::endl;
    return true;
}

//END OF CLAUDE


SDL_GPUTexture* View::loadTextureFromFile(const std::string& theFilename) {

    return nullptr;
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

    const size_t imageSize = myTilesetWidth * myTilesetHeight * 4; // RGBA8
    SDL_GPUTransferBufferCreateInfo tinfo = {};
    tinfo.size = imageSize;
    tinfo.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;

    SDL_GPUTransferBuffer* transBuffer = SDL_CreateGPUTransferBuffer(myDevice, &tinfo);

    // Map and copy pixels
    void* mapped = SDL_MapGPUTransferBuffer(myDevice, transBuffer, false);
    memcpy(mapped, data, imageSize);
    SDL_UnmapGPUTransferBuffer(myDevice, transBuffer);

    // Upload the image data
    SDL_GPUCommandBuffer* uploadBuffer = SDL_AcquireGPUCommandBuffer(myDevice);
    SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(uploadBuffer);

    SDL_GPUTextureTransferInfo transferInfo = {};
    transferInfo.transfer_buffer = transBuffer;
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
    return myTileUVMap[DunText::DungeonTile::VerticalDoor];
}

//END OF CLAUDE


void View::observeDungeon(Dungeon* theDungeon) {
    if (!theDungeon) throw SDLException{"Dungeon is null"};

    theDungeon->attach(std::shared_ptr<Observer>(this));
}


void View::unobserveDungeon(Dungeon* theDungeon) {
    if (!theDungeon) throw SDLException{"Failed to null Dungeon"};

    theDungeon->detach(std::shared_ptr<Observer>(this));

}


void View::observeCharacter(AbstractCharacter* theCharacter) {
    if (!theCharacter) throw SDLException{"Failed to observe character"};

    theCharacter->attach(std::shared_ptr<Observer>(this));

    //May need to include data structure that holds active chars
}


void View::unobserveCharacter(AbstractCharacter* theCharacter) {
    if (!theCharacter) throw SDLException{"Failed to unobserve character"};

    theCharacter->detach(std::shared_ptr<Observer>(this));

    //May need to remove from data structure that holds active chars
}


void View::Update(Subject* theChangedSubject, const std::string& thePropertyName) {

}


void View::drawRoom(SDL_GPUCommandBuffer* theCommandBuffer, SDL_GPURenderPass* theRenderPass,
    const std::vector<std::vector<DunText::DungeonTile>>& theRoomMap) {

    int windowWidth, windowHeight;
    SDL_GetWindowSize(myWindow, &windowWidth, &windowHeight);

    if (!myTilesetTexture || !myGraphicsPipeline) {
        std::cout << "Warning: Cannot render room - missing texture or pipeline" << std::endl;
        return;
    }

    if (theRoomMap.empty() || theRoomMap[0].empty()) {
        std::cout << "Warning: Empty tile map provided" << std::endl;
        return;
    }

    const int mapHeight = theRoomMap.size();
    const int mapWidth = theRoomMap[0].size();

    // Calculate scaling to fit the room nicely on screen
    float tilePixelSize = 16.0f; // Your tiles are 16x16 pixels
    float scaleX = windowWidth / (mapWidth * tilePixelSize);
    float scaleY = windowHeight / (mapHeight * tilePixelSize);
    float scale = std::min(scaleX, scaleY); // Use smaller scale to maintain aspect ratio

    // Calculate offsets to center the room
    float totalRoomWidth = mapWidth * tilePixelSize * scale;
    float totalRoomHeight = mapHeight * tilePixelSize * scale;
    float offsetX = (windowWidth - totalRoomWidth) / 2.0f;
    float offsetY = (windowHeight - totalRoomHeight) / 2.0f;

    // Bind the graphics pipeline
    SDL_BindGPUGraphicsPipeline(theRenderPass, myGraphicsPipeline);

    // Bind vertex buffer
    SDL_GPUBufferBinding vertexBinding = {};
    vertexBinding.buffer = myVertexBuffer;
    vertexBinding.offset = 0;
    SDL_BindGPUVertexBuffers(theRenderPass, 0, &vertexBinding, 1);

    // Bind index buffer
    SDL_GPUBufferBinding indexBinding = {};
    indexBinding.buffer = myIndexBuffer;
    indexBinding.offset = 0;
    SDL_BindGPUIndexBuffer(theRenderPass, &indexBinding, SDL_GPU_INDEXELEMENTSIZE_16BIT);

    // Bind texture and sampler
    /*
    SDL_GPUTextureSamplerBinding textureSamplerBinding = {};
    textureSamplerBinding.texture = myTilesetTexture;
    textureSamplerBinding.sampler = mySampler;
    SDL_BindGPUFragmentSamplers(theRenderPass, 0, &textureSamplerBinding, 1);
    */

    for (int row = 0; row < mapHeight; ++row) {
        for (int col = 0; col < mapWidth; ++col) {
            DunText::DungeonTile currentTile = theRoomMap[row][col];
            if (currentTile == DunText::DungeonTile::Blank)
                continue;

            float worldX = offsetX + (col * tilePixelSize * scale);
            float worldY = offsetY + (row * tilePixelSize * scale);
            float tileWidth  = tilePixelSize * scale;
            float tileHeight = tilePixelSize * scale;

            float ndcX = (worldX / windowWidth) * 2.0f - 1.0f;
            float ndcY = 1.0f - (worldY / windowHeight) * 2.0f;
            float ndcWidth  = (tileWidth  / windowWidth)  * 2.0f;
            float ndcHeight = (tileHeight / windowHeight) * 2.0f;

            TileUV uv = getTileUV(currentTile);
            float u = (uv.x * TILE_SIZE) / static_cast<float>(myTilesetWidth);
            float v = (uv.y * TILE_SIZE) / static_cast<float>(myTilesetHeight);
            float uvWidth  = TILE_SIZE / static_cast<float>(myTilesetWidth);
            float uvHeight = TILE_SIZE / static_cast<float>(myTilesetHeight);

            TileUniform uniform = {};
            uniform.position[0] = ndcX;
            uniform.position[1] = ndcY;
            uniform.scale[0]    = ndcWidth;
            uniform.scale[1]    = ndcHeight;
            uniform.uvOffset[0] = u;
            uniform.uvOffset[1] = v;
            uniform.uvScale[0]  = uvWidth;
            uniform.uvScale[1]  = uvHeight;

            // Push the uniform data into slot 0 for vertex shaders:
            //SDL_PushGPUVertexUniformData(theCommandBuffer, 0, &uniform, sizeof(TileUniform));

            SDL_DrawGPUIndexedPrimitives(theRenderPass, 6, 1, 0, 0, 0);
        }
    }
}


void View::drawSprite(SDL_GPURenderPass* theRenderPass, SDL_GPUTexture* theTexture, float theX, float theY) {

}