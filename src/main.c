#define GLFW_INCLUDE_VULKAN
#include "core/core.h"

int main() {

    VulkanCore core = initCore();
    RenderState renderState = initRenderState(&core);
    run(&core, &renderState);
    destroy(&core, &renderState);

    return 0;
}
