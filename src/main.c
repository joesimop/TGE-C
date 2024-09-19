#define GLFW_INCLUDE_VULKAN
#include "core/core.h"

int main() {

    VulkanCore engine = initCore();
    run(&engine);
    destroy(&engine);

    return 0;
}
