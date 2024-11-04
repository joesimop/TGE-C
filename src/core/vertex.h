#ifndef VERTEX_H
#define VERTEX_H

#include "../include/utils/types.h"
#include "buffers.h"
#include "global.h"

// Define the formats for each type size
#define ATTRIBUTE_FORMAT_FLOAT VK_FORMAT_R32_SFLOAT
#define ATTRIBUTE_FORMAT_VEC2  VK_FORMAT_R32G32_SFLOAT
#define ATTRIBUTE_FORMAT_VEC3  VK_FORMAT_R32G32B32_SFLOAT
#define ATTRIBUTE_FORMAT_VEC4  VK_FORMAT_R32G32B32A32_SFLOAT

typedef struct {
    vec2 pos;
    vec3 color;
} ShaderVertex;

extern const ShaderVertex vertices[3];

// typedef struct {
//     DYNAMIC_ARRAY(VkVertexInputBindingDescription) bindings;
//     DYNAMIC_ARRAY(VkVertexInputAttributeDescription) attributes;
// } VertexShaderManager;

/* CONVENIENCE INITIALIZERS */

/* Standardized creation for Vertex Binding Descriptions */
#define VERTEX_BINDING_DESC(__b_id)                                                                                    \
    {.binding = (__b_id), .stride = sizeof(ShaderVertex), .inputRate = VK_VERTEX_INPUT_RATE_VERTEX}

/* Standardized creation for Vertex Attribute Descriptions */
#define VERTEX_ATTRIBUTE_DESC(__b_id, __loc, __att, __att_frmt)                                                        \
    {                                                                                                                  \
            .binding = (__b_id),                                                                                       \
            .location = (__loc),                                                                                       \
            .format = (__att_frmt),                                                                                    \
            .offset = offsetof(ShaderVertex, __att),                                                                   \
    }

/* Creates a buffer of size in bytes that is pointed to by vertexBuffer */
void create_vertex_buffer(const VulkanCore* core, size_t size, VkBuffer* vertexBuffer);

#endif // VERTEX_H
