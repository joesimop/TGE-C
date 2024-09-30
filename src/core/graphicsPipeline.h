#pragma once

#include "global.h"
#include "../include/utils/fileio.h"

#define VIEWPORT_DYNAMIC 0
#define VIEWPORT_STATIC 1

void create_graphics_pipeline(VulkanCore* core);

VkShaderModule create_shader_module(VkDevice* logicalDevice, const char* code, size_t size);

//Stages of creating the pipeline 
VkPipelineDynamicStateCreateInfo create_dynamic_states();
VkPipelineVertexInputStateCreateInfo create_vertex_input_stage();
VkPipelineInputAssemblyStateCreateInfo create_input_assembly_stage();
VkPipelineViewportStateCreateInfo create_viewport(VulkanCore* core, u8 type);
VkPipelineRasterizationStateCreateInfo create_rasterizer_stage();
VkPipelineMultisampleStateCreateInfo create_multisampling_stage();
VkPipelineColorBlendAttachmentState create_color_blend_stage();
void create_pipeline_layout(VulkanCore* core);

//Subfunctions of stages
VkPipelineShaderStageCreateInfo create_vertex_shader_stage_info(VkShaderModule vertShaderModule);
VkPipelineShaderStageCreateInfo create_fragment_shader_stage_info(VkShaderModule fragShaderModule);