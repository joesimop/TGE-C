#define GLFW_INCLUDE_VULKAN
#include "core/core.h"

int main() {

    VulkanCore core; RenderState renderState;

    init_core(&core, &renderState);
    init_render_state(&core, &renderState);
    run(&core, &renderState);
    destroy(&core, &renderState);

    return 0;
}
