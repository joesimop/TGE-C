#include "windowSurface.h"

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan_macos.h>

void create_surface(VkInstance instance, GLFWwindow* window, VkSurfaceKHR* surface) {
    ASSERT(glfwCreateWindowSurface(instance, window, NULL, surface) == VK_SUCCESS, "Failed to create window surface!");
}