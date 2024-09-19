#pragma once

#include "global.h"
#include "glfw_init.h"
#include "vulkanInstance.h"
#include "vulkanDebugMessenger.h"
#include "windowSurface.h"
#include "physicalDevice.h"
#include "logicalDevice.h"
#include "swapChain.h"
#include "imageView.h"


///Initializes the engine
/// @return The intilized core to run the game
VulkanCore initCore();
void destroy(VulkanCore* engine);
void run(VulkanCore* engine);