#pragma once

#ifndef GLFW_INIT_H
#define GLFW_INIT_H
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "../include/utils/types.h"
#include "../include/utils/assertions.h"

static const u32 WIDTH = 800;
static const u32 HEIGHT = 600;

///Initializes the GLFW window
/// @return The GLFW window
void init_window(GLFWwindow** window);

#endif