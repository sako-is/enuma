#pragma once

#include <GLFW/glfw3.h>
#include <vulkan.h>

#include "defines.h"

typedef enum Backend {
    Vulkan, 
    OpenGL,
    DirectX
} Backend;

typedef union Instance {
    VkInstance instance;
} Instance;

typedef struct Engine {
    int32 w, h;
    Backend backend;
    Instance instance;
    GLFWwindow* window;
    char* name;

    void (*onStart)();
    void (*Update)();
} Engine;

ENMAPI Engine createEngine(int w, int h, Backend backend, const char* name);
ENMAPI void startEngine(Engine* engine);
ENMAPI void destroyEngine(Engine* engine);