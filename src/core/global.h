#pragma once


// BASIC DEFINES
#include <stdbool.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "../include/utils/types.h"
#include "../include/structs/dynamicarray.h"

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

// Stores the details of the swap chain
typedef struct {
    VkSurfaceCapabilitiesKHR capabilities;
    DYNAMIC_ARRAY(VkSurfaceFormatKHR) formats;
    DYNAMIC_ARRAY(VkPresentModeKHR) presentModes;
} SwapChainSupportDetails;

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

    //Not necessary, but limits function calls
    QueueFamilyIndices indices;
    SwapChainSupportDetails swapChainDetails;

    //Swap chain
    VkSwapchainKHR swapChain;
    u32 swapChainImageCount;
    VkImage* swapChainImages;
    VkImageView* swapChainImageViews;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    //Graphics pipeline
    VkPipelineShaderStageCreateInfo* shaderStageInfo;
    VkPipelineLayout pipelineLayout;
    VkRenderPass renderPass;
    VkPipeline pipeline;

} VulkanCore;