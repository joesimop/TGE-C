#define GLFW_INCLUDE_VULKAN
#include "core/core.h"

int main() {

    core_t engine = initCore();
    run(&engine);
    destroy(&engine);

    return 0;
}
