#pragma once

#include <stdbool.h>
#include <vulkan/vulkan.h>

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