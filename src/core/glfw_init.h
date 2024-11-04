#pragma once

#define GLFW_INCLUDE_VULKAN

#include "../include/utils/assertions.h"
#include "../include/utils/types.h"
#include "GLFW/glfw3.h"
#include "global.h"

static const u32 WIDTH = 800;
static const u32 HEIGHT = 600;

/// Initializes the GLFW window
///  @return The GLFW window
void init_window(GLFWwindow** window, RenderState* renderState);

// Callback function on window resize
static void frame_buffer_resize_callback(GLFWwindow* window, int width, int height);
