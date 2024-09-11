#include "core.h"
#include "global.h"

core_t initCore() {
    core_t engine;
    VkInstance instance;
    engine.window = initWindow();
    InitVulkan(&engine.instance);
    setupDebugMessenger(&engine.instance);
    return engine;
}

void run(core_t* engine) {
    while (!glfwWindowShouldClose(engine->window)) {
        glfwPollEvents();
    }
}

void destroy(core_t* engine) {
    if (enableValidationLayers) {
        DestroyDebugMessenger(engine->instance);
    }
    vkDestroyInstance(engine->instance, NULL);
    glfwDestroyWindow(engine->window);
    glfwTerminate();
}