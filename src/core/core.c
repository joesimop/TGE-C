#include "core.h"
#include "global.h"

core_t initCore() {
    core_t engine;
    VkInstance instance;
    init_window(&engine.window);
    init_vulkan(&engine.instance);
    setup_debug_messenger(&engine.instance);
    create_surface(engine.instance, engine.window, &engine.surface);
    pick_physical_device(engine.instance, engine.surface, &engine.physicalDevice);
    create_logical_device(engine.physicalDevice, engine.surface, &engine.logicalDevice, &engine.graphicsQueue);
    return engine;
}

void run(core_t* engine) {
    printf("Running\n");
    while (!glfwWindowShouldClose(engine->window)) {
        glfwPollEvents();
    }
    printf("Closing\n");
}

void destroy(core_t* engine) {
    if (ENABLE_VALIDATION_LAYERS) {
        destroy_debug_messenger(engine->instance);
    }
    destroy_logical_device(engine->logicalDevice);
    vkDestroySurfaceKHR(engine->instance, engine->surface, NULL);
    vkDestroyInstance(engine->instance, NULL);
    glfwDestroyWindow(engine->window);
    glfwTerminate();
}