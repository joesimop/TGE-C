#include "graphicsPipeline.h"

void create_graphics_pipeline(VulkanCore* core){

    char* vertShaderCode;
    size_t vertShaderSize;
    read_shader("vert.spv", &vertShaderCode, &vertShaderSize);

    char* fragShaderCode;
    size_t fragShaderSize;
    read_shader("frag.spv", &fragShaderCode, &fragShaderSize);

    VkShaderModule vertShaderModule = create_shader_module(&core->logicalDevice, vertShaderCode, vertShaderSize);
    VkShaderModule fragShaderModule = create_shader_module(&core->logicalDevice, fragShaderCode, fragShaderSize);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo = create_vertex_shader_stage_info(vertShaderModule);
    VkPipelineShaderStageCreateInfo fragShaderStageInfo = create_fragment_shader_stage_info(fragShaderModule);

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};
    core->shaderStageInfo = shaderStages;

    vkDestroyShaderModule(core->logicalDevice, fragShaderModule, NULL);
    vkDestroyShaderModule(core->logicalDevice, vertShaderModule, NULL);

    //Create the pipeline layout
    create_pipeline_layout(core);
}

VkPipelineDynamicStateCreateInfo create_dynamic_states() {
    
    VkPipelineDynamicStateCreateInfo dynamicStateInfo;

    VkDynamicState dynamicStates[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_LINE_WIDTH
    };

    dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicStateInfo.dynamicStateCount = ARRAY_SIZE(dynamicStates);
    dynamicStateInfo.pDynamicStates = dynamicStates;
    dynamicStateInfo.pNext = NULL;

    return dynamicStateInfo;
}

VkPipelineVertexInputStateCreateInfo create_vertex_input_stage(){

    VkPipelineVertexInputStateCreateInfo vertexInputInfo;
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = NULL;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = NULL;
    vertexInputInfo.pNext = NULL;

    return vertexInputInfo;
}

VkPipelineInputAssemblyStateCreateInfo create_input_assembly_stage() {

    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;
    inputAssembly.pNext = NULL;

    return inputAssembly;
}

VkPipelineViewportStateCreateInfo create_viewport(VulkanCore* core, u8 type) {
    VkViewport viewport;
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) core->swapChainExtent.width;
    viewport.height = (float) core->swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor;
    scissor.offset = (VkOffset2D) {0, 0};
    scissor.extent = core->swapChainExtent;

    VkPipelineViewportStateCreateInfo viewportState;
    if(type == VIEWPORT_DYNAMIC){

        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.scissorCount = 1;
        viewportState.pNext = NULL;

    } else {
        
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;
        viewportState.pNext = NULL;
    }

    return viewportState;
}

VkPipelineRasterizationStateCreateInfo create_rasterizer_stage(){

    VkPipelineRasterizationStateCreateInfo rasterizer;
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;

    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;

    return rasterizer;

}

VkPipelineMultisampleStateCreateInfo create_multisampling_stage(){

    VkPipelineMultisampleStateCreateInfo multisampling;
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f;
    multisampling.pSampleMask = NULL;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable = VK_FALSE;
    multisampling.pNext = NULL;

    return multisampling;
}

VkPipelineColorBlendAttachmentState create_color_blend_stage(){

    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    //For alpha blending
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    return colorBlendAttachment;
}

void create_pipeline_layout(VulkanCore* core){

    VkPipelineLayoutCreateInfo pipelineLayoutInfo;
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0; // Optional
    pipelineLayoutInfo.pSetLayouts = NULL; // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = NULL; // Optional
    pipelineLayoutInfo.flags = 0;
    pipelineLayoutInfo.pNext = NULL;


    ASSERT(vkCreatePipelineLayout(core->logicalDevice, &pipelineLayoutInfo, NULL, &core->pipelineLayout) == VK_SUCCESS, "Failed to create pipeline layout");
}

VkShaderModule create_shader_module(VkDevice* logicalDevice, const char* code, size_t size) {
    VkShaderModuleCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = size;
    createInfo.pCode = (u32*) code;

    VkShaderModule shaderModule;
    ASSERT(vkCreateShaderModule(*logicalDevice, &createInfo, NULL, &shaderModule) == VK_SUCCESS, "Failed to create shader module");

    return shaderModule;
}

VkPipelineShaderStageCreateInfo create_vertex_shader_stage_info(VkShaderModule vertShaderModule) {
    VkPipelineShaderStageCreateInfo info;
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info.stage = VK_SHADER_STAGE_VERTEX_BIT;
    info.module = vertShaderModule;
    info.pSpecializationInfo = NULL;
    info.pNext = NULL;
    info.pName = "main";

    return info;
}

VkPipelineShaderStageCreateInfo create_fragment_shader_stage_info(VkShaderModule fragShaderModule) {
    VkPipelineShaderStageCreateInfo info;
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    info.module = fragShaderModule;
    info.pSpecializationInfo = NULL;
    info.pNext = NULL;
    info.pName = "main";

    return info;
}