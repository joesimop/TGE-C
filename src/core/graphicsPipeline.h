#pragma once

#include "../include/utils/fileio.h"
#include "global.h"
#include "vertex.h"

#define VIEWPORT_DYNAMIC 0
#define VIEWPORT_STATIC  1

static const VkDynamicState dynamicStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

void create_graphics_pipeline(VulkanCore* core);

void create_shaders(VulkanCore* core);

void create_shader_module(VkDevice* logicalDevice, const char* code, size_t size, VkShaderModule* shaderModule);

// Stages of creating the pipeline
void create_dynamic_states(VkPipelineDynamicStateCreateInfo* dynamicStateInfo);
void create_vertex_input_stage(VkPipelineVertexInputStateCreateInfo* vertexInputInfo);
void create_input_assembly_stage(VkPipelineInputAssemblyStateCreateInfo* inputAssembly);

void create_viewport(VulkanCore* core, VkViewport* viewport);
void create_scissor(VulkanCore* core, VkRect2D* scissor);
void create_viewport_info(
        u8 type, VkViewport* viewport, VkRect2D* scissor, VkPipelineViewportStateCreateInfo* viewportState
);
void create_rasterizer_stage(VkPipelineRasterizationStateCreateInfo* rasterizer);
void create_multisampling_stage(VkPipelineMultisampleStateCreateInfo* multisampling);
void create_color_blend_stage(VkPipelineColorBlendAttachmentState* colorBlendAttachment);
void create_color_blend_state(
        VkPipelineColorBlendAttachmentState* colorBlendAttachment, VkPipelineColorBlendStateCreateInfo* colorBlend
);
void create_pipeline_layout(VulkanCore* core);

// Subfunctions of stages
void create_vertex_shader_stage_info(VkShaderModule vertShaderModule, VkPipelineShaderStageCreateInfo* info);
void create_fragment_shader_stage_info(VkShaderModule fragShaderModule, VkPipelineShaderStageCreateInfo* info);
