#pragma once

#include <stdbool.h>
#include <vulkan/vulkan.h>

static const char* validationLayers[] = {
    "VK_LAYER_KHRONOS_validation"
};
    

#ifdef DEBUG
    static const bool enableValidationLayers = true;
#else
    static const bool enableValidationLayers = false;
#endif

///The global debug messenger struct
VkDebugUtilsMessengerEXT debugMessenger;