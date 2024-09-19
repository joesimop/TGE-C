#pragma once


// BASIC DEFINES
#include <stdbool.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "../include/utils/types.h"

#define VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME "VK_KHR_portability_subset"
#define VK_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME "VK_KHR_get_physical_device_properties2"
#define VK_EXT_METAL_SURFACE_EXTENSION_NAME "VK_EXT_metal_surface"

static const char* VALIDATION_LAYERS[] = {
    "VK_LAYER_KHRONOS_validation"
};

static const char* DEVICE_EXTENSIONS[] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
    
#ifdef DEBUG
    static const bool ENABLE_VALIDATION_LAYERS = true;
#else
    static const bool ENABLE_VALIDATION_LAYERS = false;
#endif

// STRUCTS
// Represents queue families for physical and logical devices
typedef struct {
    opt_u32 graphicsFamily;
    opt_u32 presentFamily;
} QueueFamilyIndices;

static bool __is_valid_queue_family(QueueFamilyIndices indices){
    return has_value(indices.graphicsFamily) && has_value(indices.presentFamily);
}

///The global debug messenger struct
VkDebugUtilsMessengerEXT g_debugMessenger;

typedef struct {
    GLFWwindow* window;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSwapchainKHR swapChain;

    QueueFamilyIndices indices;
} VulkanCore;



// MACROS

//Assert
#define ASSERT(condition, ...)                                                                                 \
    do {                                                                                                       \
        if (!(condition)) {                                                                                    \
            fprintf(stderr, "\n**********************************************************\n");                 \
            fprintf(stderr, "Assertion failed: %s\n", #condition);                                             \
            fprintf(stderr, "Error: %s\n", is_empty(__VA_ARGS__) ? "No message" : #__VA_ARGS__);               \
            fprintf(stderr, "File: %s, Line: %d\n", __FILE__, __LINE__);                                       \
            fprintf(stderr, "**********************************************************\n");                   \
            exit(EXIT_FAILURE);                                                                                \
        }                                                                                                      \
    } while (0)