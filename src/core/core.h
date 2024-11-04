#pragma once

#include "buffers.h"
#include "commandPool.h"
#include "frameBuffer.h"
#include "glfw_init.h"
#include "global.h"
#include "graphicsPipeline.h"
#include "imageView.h"
#include "logicalDevice.h"
#include "physicalDevice.h"
#include "renderPass.h"
#include "swapChain.h"
#include "syncObjects.h"
#include "vertex.h"
#include "vulkanDebugMessenger.h"
#include "vulkanInstance.h"
#include "windowSurface.h"

/// Initializes the engine
///  @return The intilized core to run the game
void init_core(VulkanCore* core, RenderState* renderState);
void init_render_state(VulkanCore* core, RenderState* renderState);
void destroy(VulkanCore* core, RenderState* renderState);
void run(VulkanCore* core, RenderState* renderState);
void draw_frame(RenderState* renderState);
void construct_render_state(VulkanCore* core, RenderState* renderState);
