#pragma once

#include <vulkan.h>
#include "core/app.h"

VulkanInstance initVulkan(Engine* engine);
VulkanInstance createInstance(const char* name);
bool checkValidationLayerSupport();
void pickPhysicalDevice(VkInstance* instance);