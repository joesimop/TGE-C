#include "graphicsPipeline.h"


void create_graphics_pipeline(VulkanCore* core) {

    // Create shader instances
    char* vertShaderCode;
    size_t vertShaderSize;
    read_shader("vert.spv", &vertShaderCode, &vertShaderSize);

    char* fragShaderCode;
    size_t fragShaderSize;
    read_shader("frag.spv", &fragShaderCode, &fragShaderSize);

    VkShaderModule vertShaderModule;
    create_shader_module(&core->logicalDevice, vertShaderCode, vertShaderSize, &vertShaderModule);

    VkShaderModule fragShaderModule;
    create_shader_module(&core->logicalDevice, fragShaderCode, fragShaderSize, &fragShaderModule);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo;
    create_vertex_shader_stage_info(vertShaderModule, &vertShaderStageInfo);

    VkPipelineShaderStageCreateInfo fragShaderStageInfo;
    create_fragment_shader_stage_info(fragShaderModule, &fragShaderStageInfo);

    VkPipelineShaderStageCreateInfo* stages = malloc(sizeof(VkPipelineShaderStageCreateInfo) * 2);
    stages[0] = vertShaderStageInfo;
    stages[1] = fragShaderStageInfo;

    core->shaderStageInfo = stages;

    // Create the pipeline layout
    create_pipeline_layout(core);

    VkPipelineVertexInputStateCreateInfo vertexInputInfo;
    create_vertex_input_stage(&vertexInputInfo);

    VkVertexInputBindingDescription bindingDescription = VERTEX_BINDING_DESC(0);

    VkVertexInputAttributeDescription attribute1 = VERTEX_ATTRIBUTE_DESC(0, 0, pos, ATTRIBUTE_FORMAT_VEC2);
    VkVertexInputAttributeDescription attribute2 = VERTEX_ATTRIBUTE_DESC(0, 1, color, ATTRIBUTE_FORMAT_VEC3);

    const VkVertexInputAttributeDescription attributeList[2] = {attribute1, attribute2};

    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.pVertexAttributeDescriptions = attributeList;


    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    create_input_assembly_stage(&inputAssembly);

    // Viewport State using viewport and scissor
    VkViewport viewport;
    create_viewport(core, &viewport);

    VkRect2D scissor;
    create_scissor(core, &scissor);

    VkPipelineViewportStateCreateInfo viewportState;
    create_viewport_info(VIEWPORT_DYNAMIC, &viewport, &scissor, &viewportState);


    VkPipelineRasterizationStateCreateInfo rasterizer;
    create_rasterizer_stage(&rasterizer);


    VkPipelineMultisampleStateCreateInfo multisampling;
    create_multisampling_stage(&multisampling);

    // Create Color blend attachment
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    create_color_blend_stage(&colorBlendAttachment);


    VkPipelineColorBlendStateCreateInfo colorBlend;
    create_color_blend_state(&colorBlendAttachment, &colorBlend);

    VkPipelineDynamicStateCreateInfo dynamicState;
    create_dynamic_states(&dynamicState);
    dynamicState.dynamicStateCount = ARRAY_SIZE(dynamicStates);
    dynamicState.pDynamicStates = dynamicStates;

    VkGraphicsPipelineCreateInfo pipelineInfo;
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = core->shaderStageInfo;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = NULL;
    pipelineInfo.pColorBlendState = &colorBlend;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = core->pipelineLayout;
    pipelineInfo.renderPass = core->renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = -1;

    // Necessities
    pipelineInfo.pNext = NULL;
    pipelineInfo.flags = 0;
    pipelineInfo.pTessellationState = NULL;

    ASSERT(vkCreateGraphicsPipelines(core->logicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, &core->pipeline) ==
                   VK_SUCCESS,
           "Failed to create graphics pipeline");

    vkDestroyShaderModule(core->logicalDevice, fragShaderModule, NULL);
    vkDestroyShaderModule(core->logicalDevice, vertShaderModule, NULL);
    free(vertShaderCode);
    free(fragShaderCode);
}

void create_shaders(VulkanCore* core) {

    char* vertShaderCode;
    size_t vertShaderSize;
    read_shader("vert.spv", &vertShaderCode, &vertShaderSize);

    char* fragShaderCode;
    size_t fragShaderSize;
    read_shader("frag.spv", &fragShaderCode, &fragShaderSize);

    VkShaderModule vertShaderModule;
    create_shader_module(&core->logicalDevice, vertShaderCode, vertShaderSize, &vertShaderModule);

    VkShaderModule fragShaderModule;
    create_shader_module(&core->logicalDevice, fragShaderCode, fragShaderSize, &fragShaderModule);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo;
    create_vertex_shader_stage_info(vertShaderModule, &vertShaderStageInfo);

    VkPipelineShaderStageCreateInfo fragShaderStageInfo;
    create_fragment_shader_stage_info(fragShaderModule, &fragShaderStageInfo);

    VkPipelineShaderStageCreateInfo* stages =
            (VkPipelineShaderStageCreateInfo*) malloc(sizeof(VkPipelineShaderStageCreateInfo) * 2);
    stages[0] = vertShaderStageInfo;
    stages[1] = fragShaderStageInfo;

    core->shaderStageInfo = stages;
}

void create_pipeline_layout(VulkanCore* core) {

    VkPipelineLayoutCreateInfo pipelineLayoutInfo;
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;         // Optional
    pipelineLayoutInfo.pSetLayouts = NULL;         // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = NULL; // Optional
    pipelineLayoutInfo.flags = 0;
    pipelineLayoutInfo.pNext = NULL;


    ASSERT(vkCreatePipelineLayout(core->logicalDevice, &pipelineLayoutInfo, NULL, &core->pipelineLayout) == VK_SUCCESS,
           "Failed to create pipeline layout");
}


void create_dynamic_states(VkPipelineDynamicStateCreateInfo* dynamicStateInfo) {

    dynamicStateInfo->sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicStateInfo->pNext = NULL;
    dynamicStateInfo->flags = 0;
}

void create_vertex_input_stage(VkPipelineVertexInputStateCreateInfo* vertexInputInfo) {

    vertexInputInfo->sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo->vertexBindingDescriptionCount = 1;
    // vertexInputInfo->pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo->vertexAttributeDescriptionCount = 2;
    // vertexInputInfo->pVertexAttributeDescriptions = &attributeList;
    vertexInputInfo->pNext = NULL;
    vertexInputInfo->flags = 0;
}

void create_input_assembly_stage(VkPipelineInputAssemblyStateCreateInfo* inputAssembly) {

    inputAssembly->sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly->topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly->primitiveRestartEnable = VK_FALSE;
    inputAssembly->pNext = NULL;
    inputAssembly->flags = 0;
}

void create_viewport(VulkanCore* core, VkViewport* viewport) {
    viewport->x = 0.0f;
    viewport->y = 0.0f;
    viewport->width = (float) core->swapChainExtent.width;
    viewport->height = (float) core->swapChainExtent.height;
    viewport->minDepth = 0.0f;
    viewport->maxDepth = 1.0f;
}

void create_scissor(VulkanCore* core, VkRect2D* scissor) {
    scissor->offset = (VkOffset2D) {0, 0};
    scissor->extent = core->swapChainExtent;
}

void create_viewport_info(
        u8 type, VkViewport* viewport, VkRect2D* scissor, VkPipelineViewportStateCreateInfo* viewportState
) {

    if (type == VIEWPORT_DYNAMIC) {

        viewportState->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState->viewportCount = 1;
        viewportState->scissorCount = 1;


    } else {

        viewportState->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState->viewportCount = 1;
        viewportState->pViewports = viewport;
        viewportState->scissorCount = 1;
        viewportState->pScissors = scissor;
    }

    viewportState->pNext = NULL;
    viewportState->flags = 0;
}

void create_rasterizer_stage(VkPipelineRasterizationStateCreateInfo* rasterizer) {

    rasterizer->sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer->depthClampEnable = VK_FALSE;
    rasterizer->depthClampEnable = VK_FALSE;
    rasterizer->rasterizerDiscardEnable = VK_FALSE;
    rasterizer->polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer->lineWidth = 1.0f;
    rasterizer->cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer->frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer->depthBiasEnable = VK_FALSE;
    rasterizer->depthBiasConstantFactor = 0.0f;
    rasterizer->depthBiasClamp = 0.0f;
    rasterizer->flags = 0;
    rasterizer->pNext = NULL;
}

void create_multisampling_stage(VkPipelineMultisampleStateCreateInfo* multisampling) {

    multisampling->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling->sampleShadingEnable = VK_FALSE;
    multisampling->rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling->minSampleShading = 1.0f;
    multisampling->pSampleMask = NULL;
    multisampling->alphaToCoverageEnable = VK_FALSE;
    multisampling->alphaToOneEnable = VK_FALSE;
    multisampling->pNext = NULL;
    multisampling->flags = 0;
}

void create_color_blend_stage(VkPipelineColorBlendAttachmentState* colorBlendAttachment) {

    colorBlendAttachment->colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    // For alpha blendining
    colorBlendAttachment->blendEnable = VK_TRUE;
    colorBlendAttachment->srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachment->dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment->colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment->srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment->dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment->alphaBlendOp = VK_BLEND_OP_ADD;
}

void create_color_blend_state(
        VkPipelineColorBlendAttachmentState* colorBlendAttachment, VkPipelineColorBlendStateCreateInfo* colorBlending
) {

    colorBlending->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending->logicOpEnable = VK_FALSE;
    colorBlending->logicOp = VK_LOGIC_OP_COPY;
    colorBlending->attachmentCount = 1;
    colorBlending->pAttachments = colorBlendAttachment;
    colorBlending->blendConstants[0] = 0.0f;
    colorBlending->blendConstants[1] = 0.0f;
    colorBlending->blendConstants[2] = 0.0f;
    colorBlending->blendConstants[3] = 0.0f;
    colorBlending->pNext = NULL;
    colorBlending->flags = 0;
}


void create_shader_module(VkDevice* logicalDevice, const char* code, size_t size, VkShaderModule* shaderModule) {

    VkShaderModuleCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = size;
    createInfo.pCode = (u32*) code;
    createInfo.pNext = NULL;
    createInfo.flags = 0;

    ASSERT(vkCreateShaderModule(*logicalDevice, &createInfo, NULL, shaderModule) == VK_SUCCESS,
           "Failed to create shader module");
}

void create_vertex_shader_stage_info(VkShaderModule vertShaderModule, VkPipelineShaderStageCreateInfo* info) {

    info->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info->stage = VK_SHADER_STAGE_VERTEX_BIT;
    info->module = vertShaderModule;
    info->pSpecializationInfo = NULL;
    info->pNext = NULL;
    info->flags = 0;
    info->pName = "main";
}

void create_fragment_shader_stage_info(VkShaderModule fragShaderModule, VkPipelineShaderStageCreateInfo* info) {

    info->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info->stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    info->module = fragShaderModule;
    info->pSpecializationInfo = NULL;
    info->pNext = NULL;
    info->flags = 0;
    info->pName = "main";
}
