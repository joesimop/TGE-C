#include "commandPool.h"

void create_command_pool(RenderState* renderState) {

    VkCommandPoolCreateInfo poolInfo;
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = renderState->core->indices.graphicsFamily.value;
    poolInfo.pNext = NULL;

    ASSERT(vkCreateCommandPool(renderState->core->logicalDevice, &poolInfo, NULL, &renderState->commandPool) == VK_SUCCESS, "Failed to create command pool");
}

void create_command_buffer(RenderState* renderState){
    
        VkCommandBufferAllocateInfo allocInfo;
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = renderState->commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = MAX_FRAMES_IN_FLIGHT;
        allocInfo.pNext = NULL;
    
        ASSERT(vkAllocateCommandBuffers(renderState->core->logicalDevice, &allocInfo, renderState->commandBuffers) == VK_SUCCESS, "Failed to allocate command buffer");
}

void record_command_buffer(RenderState* renderState) {

    //Easy access to the current command buffer
    VkCommandBuffer* currentCommandBuffer = &renderState->commandBuffers[renderState->currentFrame];

    VkCommandBufferBeginInfo beginInfo;
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = NULL;
    beginInfo.pNext = NULL;
    
    ASSERT(vkBeginCommandBuffer(*currentCommandBuffer, &beginInfo) == VK_SUCCESS, "Failed to begin recording command buffer");
    
    VkRenderPassBeginInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderState->core->renderPass;
    renderPassInfo.framebuffer = renderState->core->swapChainFramebuffers[renderState->scImageIndex];
    renderPassInfo.renderArea.offset = (VkOffset2D) {0, 0};
    renderPassInfo.renderArea.extent = renderState->core->swapChainExtent;

    const VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(*currentCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(*currentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, renderState->core->pipeline);

    VkViewport viewport;
    create_viewport(renderState->core, &viewport);
    vkCmdSetViewport(*currentCommandBuffer, 0, 1, &viewport);

    VkRect2D scissor;
    create_scissor(renderState->core, &scissor);
    vkCmdSetScissor(*currentCommandBuffer, 0, 1, &scissor);

    vkCmdDraw(*currentCommandBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(*currentCommandBuffer);

    ASSERT(vkEndCommandBuffer(*currentCommandBuffer) == VK_SUCCESS, "Failed to record command buffer");

}
