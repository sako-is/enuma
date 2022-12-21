#include "draw.h"

#include "log/logger.h"
#include "vulkan/vulkan.h"

Instance initRender(Engine* engine) {
    Instance instance;

    switch(engine->backend) {
        case Vulkan:
            instance = initVulkan(engine);
            break;
        case OpenGL:
            E_ERROR("OpenGL not implemented");
            break;
        case DirectX:
            E_ERROR("DirectX not implemented");
            break;
    }

    return instance;
}