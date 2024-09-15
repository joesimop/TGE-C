#pragma once

#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"
#include "../include/utils/helpers.h"

void create_surface(VkInstance instance, GLFWwindow* window, VkSurfaceKHR* surface);