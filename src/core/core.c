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
    create_image_views(&core);
    create_render_pass(&core);
    create_graphics_pipeline(&core);
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

    free(core->shaderStageInfo);
    vkDestroyPipeline(core->logicalDevice, core->pipeline, NULL);
    vkDestroyPipelineLayout(core->logicalDevice, core->pipelineLayout, NULL);
    vkDestroyRenderPass(core->logicalDevice, core->renderPass, NULL);
    destroy_image_views(core);
    destroy_swap_chain(core);
    destroy_logical_device(core->logicalDevice);
    vkDestroySurfaceKHR(core->instance, core->surface, NULL);
    vkDestroyInstance(core->instance, NULL);
    glfwDestroyWindow(core->window);
    glfwTerminate();
}