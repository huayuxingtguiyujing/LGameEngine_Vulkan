#pragma once


#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h> needed

#define TINYOBJLOADER_IMPLEMENTATION
//#include <tiny_obj_loader.h> needed

#define SDL_MAIN_HANDLED
//#include <SDL.h>,<SDL_vulkan.h> needed

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/glm.hpp> needed

#include "vulkan_RHI.h"
#include "engine.h"

#include <chrono>
#include <queue>

int main()
{
    GameEngine::Engine engine = GameEngine::Engine();
    engine.init();
    engine.tick();
    engine.end();

    return 0;
}
