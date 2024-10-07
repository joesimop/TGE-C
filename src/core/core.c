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
    create_frame_buffers(&core);
    return core;
}

RenderState initRenderState(VulkanCore* core) {
    RenderState renderState;
    fprintf(stderr, "Value: %d\n", core->indices.graphicsFamily.value);
    construct_render_state(core, &renderState);
    create_command_pool(&renderState);
    create_command_buffer(&renderState);
    create_sync_objects(&renderState);
    return renderState;
}

void run(VulkanCore* core, RenderState* renderState) {
    printf("Running\n");
    while (!glfwWindowShouldClose(core->window)) {
        glfwPollEvents();
        draw_frame(renderState);
    }
    printf("Closing\n");
    vkDeviceWaitIdle(core->logicalDevice);
}

void construct_render_state(VulkanCore* core, RenderState* renderState) {
    renderState->core = core;
    renderState->waitStages[0] = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
}

void draw_frame(RenderState* renderState){

    //Readability variables
    VulkanCore* core = renderState->core;
    u32 currentFrame = renderState->currentFrame;

    vkWaitForFences(core->logicalDevice, 1, &renderState->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
    vkResetFences(core->logicalDevice, 1, &renderState->inFlightFences[currentFrame]);

    vkAcquireNextImageKHR(core->logicalDevice, 
                            core->swapChain, 
                            UINT64_MAX, 
                            renderState->cb_waitSemaphores[currentFrame], 
                            VK_NULL_HANDLE, 
                            &renderState->scImageIndex);
    
    vkResetCommandBuffer(renderState->commandBuffers[currentFrame], 0);

    record_command_buffer(renderState);

    VkSubmitInfo submitInfo;    
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext = NULL;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = &renderState->cb_waitSemaphores[currentFrame];
    submitInfo.pWaitDstStageMask = renderState->waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &renderState->commandBuffers[currentFrame];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &renderState->signalSemaphores[currentFrame];
    vkQueueSubmit(core->graphicsQueue, 1, &submitInfo, renderState->inFlightFences[currentFrame]);


    VkPresentInfoKHR presentInfo;
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &renderState->signalSemaphores[currentFrame];
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &core->swapChain;
    presentInfo.pImageIndices = &renderState->scImageIndex;
    presentInfo.pResults = NULL;
    presentInfo.pNext = NULL;
    vkQueuePresentKHR(core->presentQueue, &presentInfo);

    renderState->currentFrame = (renderState->currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void destroy(VulkanCore* core, RenderState* renderState) {

    if (ENABLE_VALIDATION_LAYERS) {
        destroy_debug_messenger(core->instance);
    }

    destroy_sync_objects(renderState);
    vkDestroyCommandPool(core->logicalDevice, renderState->commandPool, NULL);
    destroy_frame_buffers(core);
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