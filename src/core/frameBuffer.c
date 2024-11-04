#include "frameBuffer.h"


void create_frame_buffers(VulkanCore* core) {

    da_init(core->swapChainFramebuffers, core->swapChainImageCount);

    for (size_t i = 0; i < core->swapChainImageCount; i++) {
        VkImageView* attachments = &core->swapChainImageViews[i];

        VkFramebufferCreateInfo frameBufferInfo;
        frameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        frameBufferInfo.renderPass = core->renderPass;
        frameBufferInfo.attachmentCount = 1;
        frameBufferInfo.pAttachments = attachments;
        frameBufferInfo.width = core->swapChainExtent.width;
        frameBufferInfo.height = core->swapChainExtent.height;
        frameBufferInfo.layers = 1;
        frameBufferInfo.flags = 0;
        frameBufferInfo.pNext = NULL;

        ASSERT(vkCreateFramebuffer(core->logicalDevice, &frameBufferInfo, NULL, &core->swapChainFramebuffers[i]) ==
                       VK_SUCCESS,
               "Failed to create frame buffer");
    }
}

void destroy_frame_buffers(VulkanCore* core) {
    for (int i = 0; i < core->swapChainImageCount; i++) {
        vkDestroyFramebuffer(core->logicalDevice, core->swapChainFramebuffers[i], NULL);
    }
    da_free(core->swapChainFramebuffers);
}
