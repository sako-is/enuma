#pragma once

#include <vulkan.h>
#include "core/app.h"

Instance initVulkan(Engine* engine);
VkInstance createInstance(const char* name);