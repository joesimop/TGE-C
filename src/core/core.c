#include "core.h"

VulkanCore initCore() {
    VulkanCore core;
    init_window(&core.window);
    init_vulkan(&core.instance);
    setup_debug_messenger(&core.instance);
    create_surface(&core);
    pick_physical_device(&core);
    create_logical_device(&core);
    create_swap_chain(&core);
    return core;
}

void run(VulkanCore* core) {
    printf("Running\n");
    while (!glfwWindowShouldClose(core->window)) {
        glfwPollEvents();
    }
    printf("Closing\n");
}

void destroy(VulkanCore* core) {

    if (ENABLE_VALIDATION_LAYERS) {
        destroy_debug_messenger(core->instance);
    }

    vkDestroySwapchainKHR(core->logicalDevice, core->swapChain, NULL);
    destroy_logical_device(core->logicalDevice);
    vkDestroySurfaceKHR(core->instance, core->surface, NULL);
    vkDestroyInstance(core->instance, NULL);
    glfwDestroyWindow(core->window);
    destroy_swap_chain_details(&core->swapChainDetails);
    da_free(core->swapChainImages);
    glfwTerminate();
}