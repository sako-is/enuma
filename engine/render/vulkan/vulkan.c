#include "vulkan.h"

#include "defines.h"
#include "log/logger.h"
#include "core/app.h"
#include "containers/vector.h"

#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* validation_layers[] = {"VK_LAYER_KHRONOS_validation"};
const size_t validation_layers_size = sizeof(validation_layers)/sizeof(validation_layers[0]);

#ifndef E_RELEASE
const bool enable_validation_layers = true;
#else
const bool enable_validation_layers = false;
#endif

VulkanInstance initVulkan(Engine* engine) {
	VulkanInstance result;
	result = createInstance((const char*)engine->name);
	pickPhysicalDevice(&result.vk);
	// if(result) return false;

	return result;
}

VulkanInstance createInstance(const char* name) {
    if (enable_validation_layers && !checkValidationLayerSupport()) E_ERROR("Validation layers requested, but not available"); 

    VulkanInstance vkinstance;
	VkInstance instance;

	// setting up the app info
	VkApplicationInfo app_info = {};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = name;
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "Enuma";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo create_info = {};
    if (enable_validation_layers) {
        create_info.enabledLayerCount = (uint32)(validation_layers_size);
        create_info.ppEnabledLayerNames = validation_layers;
    } else create_info.enabledLayerCount = 0;
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;

	// extensions
	uint32 glfw_extension_count = 0;
	const char** glfw_extensions;

	glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	create_info.enabledExtensionCount = glfw_extension_count;
	create_info.ppEnabledExtensionNames = glfw_extensions;
	//

	create_info.enabledLayerCount = 0;

	VkResult result = vkCreateInstance(&create_info, NULL, &instance);

	if (result != VK_SUCCESS) {
		E_ERROR("Failed to create a Vulkan Instance!\n");
		vkinstance.vk = instance;
		vkinstance.extensions = NULL;
		return vkinstance;
	}

	uint32 extension_count = 1;
	vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);

	VkExtensionProperties *extensions = malloc(sizeof(VkExtensionProperties) * extension_count);
	vkEnumerateInstanceExtensionProperties(NULL, &extension_count, extensions);

	for(int i = 0; i < extension_count; i++) {
		E_INFO("Vulkan Extension #%i: %s\n", i+1, extensions[i].extensionName);
	}

	vkinstance.vk = instance;
	vkinstance.extensions = extensions;

	return vkinstance;
}

bool checkValidationLayerSupport() {
    uint32 layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, NULL);

    VkLayerProperties* available_layers = malloc(sizeof(VkLayerProperties) * layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

    bool layer_found = false;
    for(int i = 0; i < validation_layers_size; i++) {
        for(int j = 0; j < layer_count; j++) {
            if(strcmp(validation_layers[i], available_layers[j].layerName) == 0) { layer_found = true; break; }
        }
    }

    return layer_found;
}

bool isDeviceSuitable(VkPhysicalDevice device) { return true; }

void pickPhysicalDevice(VkInstance* instance) {
	VkPhysicalDevice device = VK_NULL_HANDLE;

	uint32 device_count = 0;
	vkEnumeratePhysicalDevices(*instance, &device_count, NULL);
	if(device_count == 0) { E_ERROR("Failed to find GPU with Vulkan support\n"); return; }

    VkPhysicalDevice* devices = malloc(device_count * sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(*instance, &device_count, devices);

	for(int i = 0; i < device_count; i++) {
		if(isDeviceSuitable(devices[i])) { device = *devices; break; }
	}

	if(device == VK_NULL_HANDLE) { E_ERROR("Failed to find GPU with Vulkan support\n"); return; }

    VkPhysicalDeviceProperties* properties;
    vkGetPhysicalDeviceProperties(device, properties);

    E_INFO("GPU with Vulkan support is available, %s with ID %u", properties->deviceName, properties->deviceID);
}