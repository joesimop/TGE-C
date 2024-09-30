#include "imageView.h"

void create_image_views(VulkanCore* core) {

    u32 imageCount = core->swapChainImageCount;

    core->swapChainImageViews = malloc(sizeof(VkImageView) * imageCount);
    
    for (int i = 0; i < imageCount; i++) {
        VkImageViewCreateInfo createInfo;
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = core->swapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = core->swapChainImageFormat;
        createInfo.flags = 0;
        createInfo.pNext = NULL;


        //Can set channels to constant value or map all to red for monochrome
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        //Describes the image's purpose and which part of the image should be accessed
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        //Print location of swapchainImageView
        printf("Creating image view at %p\n", &(core->swapChainImageViews[i]));

        ASSERT(vkCreateImageView(core->logicalDevice, &createInfo, NULL, &(core->swapChainImageViews[i])) == VK_SUCCESS, "Failed to create image views!");
    }

}

void destroy_image_views(VulkanCore* core) {
    for (int i = 0; i < core->swapChainImageCount; i++) {
        vkDestroyImageView(core->logicalDevice, core->swapChainImageViews[i], NULL);
    }
    free(core->swapChainImageViews);
}

