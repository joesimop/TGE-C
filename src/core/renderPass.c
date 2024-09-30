#include "renderPass.h"


void create_render_pass(VulkanCore* core){

    VkRenderPassCreateInfo renderPassInfo;
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.flags = 0;
    renderPassInfo.pNext = NULL;

    //Color attachment
    VkAttachmentDescription colorAttachment = create_render_attachment(core);
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;

    
    VkAttachmentReference colorAttachmentRef;
    colorAttachmentRef.attachment = 0;          //Index of the attachment in the attachment array
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    //Subpasses
    VkSubpassDescription subpass = create_render_sub_pass();
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    //Dependencies
    VkSubpassDependency dependency = create_subpass_dependency();
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;
    
    ASSERT(vkCreateRenderPass(core->logicalDevice, &renderPassInfo, NULL, &core->renderPass) == VK_SUCCESS, "Failed to create render pass");
}

VkAttachmentDescription create_render_attachment(VulkanCore* core){

    VkAttachmentDescription colorAttachment;
    colorAttachment.flags = 0;

    //No multisampling, use swapchain format
    colorAttachment.format = core->swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

    //What to do with the data in the attachment before rendering
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

    //What to do with the stencil data - not using right now
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;  
   
    //How to handle the data during the render pass
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    return colorAttachment;
}

VkSubpassDescription create_render_sub_pass(){

        VkSubpassDescription subpass;
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.flags = 0;


        //Subpass necessities
        subpass.flags = 0;
        subpass.inputAttachmentCount = 0;
        subpass.preserveAttachmentCount = 0;
        subpass.pResolveAttachments = NULL;
        subpass.pDepthStencilAttachment = NULL;

        return subpass;

}

VkSubpassDependency create_subpass_dependency(){

    VkSubpassDependency dependency;
    // source
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;

	// destination
	dependency.dstSubpass = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    return dependency;
}