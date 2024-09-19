#include "windowSurface.h"


void create_surface(VulkanCore* core) {
    ASSERT(glfwCreateWindowSurface(core->instance, core->window, NULL, &core->surface) == VK_SUCCESS, "Failed to create window surface!");
}