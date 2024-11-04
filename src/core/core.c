#include "core.h"

VkBuffer only_buffer;
size_t only_buffer_size = sizeof(ShaderVertex) * ARRAY_SIZE(vertices);
VkDeviceMemory only_buffer_memory;

void init_core(VulkanCore* core, RenderState* renderState) {
    init_window(&core->window, renderState);
    init_vulkan(&core->instance);
    setup_debug_messenger(&core->instance);
    create_surface(core);
    pick_physical_device(core);
    create_logical_device(core);
    create_swap_chain(core);
    create_image_views(core);
    create_render_pass(core);
    create_graphics_pipeline(core);
    create_frame_buffers(core);
}

void init_render_state(VulkanCore* core, RenderState* renderState) {
    construct_render_state(core, renderState);
    create_vertex_buffer(core, only_buffer_size, &only_buffer);
    allocate_buffer(core, only_buffer, &only_buffer_memory, 0);
    fill_buffer(core, &only_buffer_memory, only_buffer_size, vertices, 0);
    renderState->buffer = &only_buffer;
    create_command_pool(renderState);
    create_command_buffer(renderState);
    create_sync_objects(renderState);
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
    renderState->frameBufferResized = false;
}

void draw_frame(RenderState* renderState) {

    // Readability variables
    VulkanCore* core = renderState->core;
    u32 currentFrame = renderState->currentFrame;

    vkWaitForFences(core->logicalDevice, 1, &renderState->inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    VkResult result = vkAcquireNextImageKHR(
            core->logicalDevice, core->swapChain, UINT64_MAX, renderState->cb_waitSemaphores[currentFrame],
            VK_NULL_HANDLE, &renderState->scImageIndex
    );

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreate_swap_chain(core);
        return;
    }
    ASSERT(result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR, "Failed to aquire swapchain image");

    // Only unsignal the fence if we know we are going to present
    vkResetFences(core->logicalDevice, 1, &renderState->inFlightFences[currentFrame]);

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

    result = vkQueuePresentKHR(core->presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || renderState->frameBufferResized) {
        renderState->frameBufferResized = false;
        recreate_swap_chain(core);
    } else {
        ASSERT(result == VK_SUCCESS, "Failed to present swapchain image.");
    }

    renderState->currentFrame = (renderState->currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void destroy(VulkanCore* core, RenderState* renderState) {

    if (ENABLE_VALIDATION_LAYERS) {
        destroy_debug_messenger(core->instance);
    }

    destroy_buffer(core, &only_buffer);
    vkFreeMemory(core->logicalDevice, only_buffer_memory, NULL);
    destroy_sync_objects(renderState);

    vkDestroyCommandPool(core->logicalDevice, renderState->commandPool, NULL);

    cleanup_swap_chain(core);
    destroy_swap_chain_details(&core->swapChainDetails);
    free(core->shaderStageInfo);
    vkDestroyPipeline(core->logicalDevice, core->pipeline, NULL);
    vkDestroyPipelineLayout(core->logicalDevice, core->pipelineLayout, NULL);
    vkDestroyRenderPass(core->logicalDevice, core->renderPass, NULL);
    destroy_logical_device(core->logicalDevice);
    vkDestroySurfaceKHR(core->instance, core->surface, NULL);
    vkDestroyInstance(core->instance, NULL);
    glfwDestroyWindow(core->window);
    glfwTerminate();
}
