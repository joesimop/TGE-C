#pragma once

#include <stdbool.h>
#include <vulkan/vulkan.h>

#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"
#define VK_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME "VK_KHR_get_physical_device_properties2"

static const char* VALIDATION_LAYERS[] = {
    "VK_LAYER_KHRONOS_validation"
};
    

#ifdef DEBUG
    static const bool ENABLE_VALIDATION_LAYERS = true;
#else
    static const bool ENABLE_VALIDATION_LAYERS = false;
#endif

///The global debug messenger struct
VkDebugUtilsMessengerEXT g_debugMessenger;