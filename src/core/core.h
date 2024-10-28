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
#include "graphicsPipeline.h"
#include "renderPass.h"
#include "frameBuffer.h"
#include "commandPool.h"
#include "syncObjects.h"


///Initializes the engine
/// @return The intilized core to run the game
void init_core(VulkanCore* core, RenderState* renderState);
void init_render_state(VulkanCore* core, RenderState* renderState);
void destroy(VulkanCore* core, RenderState* renderState);
void run(VulkanCore* core, RenderState* renderState);
void draw_frame(RenderState* renderState);
void construct_render_state(VulkanCore* core, RenderState* renderState);