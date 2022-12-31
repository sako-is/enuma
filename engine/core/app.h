#pragma once

#include <GLFW/glfw3.h>
#include <vulkan.h>

#include "defines.h"
#include "containers/vector.h"
#include "ecs/ecs.h"

typedef enum Backend {
    Vulkan, 
    OpenGL,
    DirectX
} Backend;

typedef struct VulkanInstance {
    VkInstance vk;
    VkExtensionProperties* extensions;
} VulkanInstance;

typedef union Instance {
    VulkanInstance vulkan;
} Instance;

/**
 * @brief struct that holds the information about the engine instance
 * @field w width of the window
 * @field h height of the window
 * @field instance instance of the graphics engine used, not meant to be used by the user
 * @field name title of the window
**/
typedef struct Engine {
    int32 w, h;
    Backend backend;
    Instance instance;
    Vector entities;
    GLFWwindow* window;
    char* name;

    void (*onStart)();
    void (*Update)();
} Engine;


/**
 * @brief creates the engine instance
 * @param w width of the window to be created
 * @param h height of the window to be created
 * @param backend graphics engine to be used
 * @param name name of the engine, any string
 * @return the engine instance
**/
ENMAPI Engine createEngine(int w, int h, Backend backend, const char* name);
ENMAPI void startEngine(Engine* engine);
ENMAPI void destroyEngine(Engine* engine);