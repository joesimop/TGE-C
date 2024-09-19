#pragma once

#include "glfw_init.h"
#include "vulkanInstance.h"
#include "vulkanDebugMessenger.h"
#include "windowSurface.h"
#include "physicalDevice.h"
#include "logicalDevice.h"
#include "swapChain.h"


typedef struct {
    GLFWwindow* window;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSwapchainKHR swapChain;
} core_t;


///Initializes the engine
/// @return The intilized core to run the game
core_t initCore();
void destroy(core_t* engine);
void run(core_t* engine);