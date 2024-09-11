#pragma once

#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H
#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"
#include "vulkanDebugMessenger.h"
#include <stdbool.h>


///Creates the Vulkan instance
void InitVulkan(VkInstance *instance);

///Creates the Vulkan instance with constants
VkInstance createVulkanInstance();

///Creates the application info constants for the Vulkan instance
void createAppInfo(VkApplicationInfo* appInfo);

///Gets glfw extensions and applies them to the createInfo, adds validation layers if enabled
void configureExtensions(VkInstanceCreateInfo* createInfo);

///Returns the required extensions for the Vulkan instance
/// @return DA(const char**) of the required extensions
const char** getRequiredExtensions();

///Returns true if the all requested validation layers are supported
bool checkValidationLayerSupport();




#endif