#include "vulkan.h"

#include "defines.h"
#include "log/logger.h"
#include "core/app.h"
#include "containers/vector.h"

#include <vulkan.h>
#include <stdio.h>
#include <stdlib.h>

Instance initVulkan(Engine* engine) {
    Instance result;
    result.instance = createInstance((const char*)engine->name);
    // if(result) return false;

    return result;
}

VkInstance createInstance(const char* name) {
    VkInstance instance;

    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = name;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Enuma";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    uint32 glfw_extension_count = 0;
    const char** glfw_extensions;

    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    create_info.enabledExtensionCount = glfw_extension_count;
    create_info.ppEnabledExtensionNames = glfw_extensions;

    create_info.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&create_info, NULL, &instance);

    if (result != VK_SUCCESS) {
        E_ERROR("Failed to create a Vulkan Instance!\n");
        return false;
    }

    uint32 extension_count = 1;
    vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);

    VkExtensionProperties *extensions = malloc(sizeof(VkExtensionProperties) * extension_count);
    vkEnumerateInstanceExtensionProperties(NULL, &extension_count, extensions);

    for(int i = 0; i < extension_count; i++) {
        E_INFO("Vulkan Extension #%i: %s\n", i+1, extensions[i].extensionName);
    }

    return instance;
}