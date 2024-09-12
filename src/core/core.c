#include "core.h"
#include "global.h"

core_t initCore() {
    core_t engine;
    VkInstance instance;
    init_window(&engine.window);
    init_vulkan(&engine.instance);
    setup_debug_messenger(&engine.instance);
    return engine;
}

void run(core_t* engine) {
    while (!glfwWindowShouldClose(engine->window)) {
        glfwPollEvents();
    }
}

void destroy(core_t* engine) {
    if (ENABLE_VALIDATION_LAYERS) {
        destroy_debug_messenger(engine->instance);
    }
    vkDestroyInstance(engine->instance, NULL);
    glfwDestroyWindow(engine->window);
    glfwTerminate();
}