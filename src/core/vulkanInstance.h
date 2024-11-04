#pragma once

#define GLFW_INCLUDE_VULKAN

#include <stdbool.h>
#include "GLFW/glfw3.h"
#include "global.h"
#include "vulkanDebugMessenger.h"

#include "../include/utils/helpers.h"

/// Creates the Vulkan instance
void init_vulkan(VkInstance* instance);

/// Creates the Vulkan instance with constants
VkInstance create_vulkan_instance();

/// Creates the application info constants for the Vulkan instance
void __create_app_info(VkApplicationInfo* appInfo);

/// Gets glfw extensions and applies them to the createInfo, adds validation layers if enabled
void __configure_extensions(VkInstanceCreateInfo* createInfo);

/// Returns the required extensions for the Vulkan instance
///  @return DA(const char**) of the required extensions
const char** __get_required_extensions();

/// Returns true if the all requested validation layers are supported
bool __check_validation_layer_support();
