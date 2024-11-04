#ifndef BUFFERS_H
#define BUFFERS_H

#include "global.h"
#include "memory.h"

/* Standardized creation for VkBuffers*/
#define BUFFER_CREATE_INFO(__s, __u, __sh)                                                                             \
    {.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,                                                                    \
     .size = (__s),                                                                                                    \
     .usage = (__u),                                                                                                   \
     .sharingMode = (__sh),                                                                                            \
     .flags = 0,                                                                                                       \
     .pNext = NULL}

/* Standardized creation for Vertex Buffer */
#define VERTEX_BUFFER_CREATE_INFO(__size, __sharing)                                                                   \
    BUFFER_CREATE_INFO((__size), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, (__sharing))

/* Allocates and binds memory for buffer and populates device_memory if successful, errors otherwise */
void allocate_buffer(const VulkanCore* core, VkBuffer buffer, VkDeviceMemory* device_memory, VkDeviceSize offset);

void fill_buffer(
        const VulkanCore* core, const VkDeviceMemory* device_memory, size_t size, const void* data, VkDeviceSize offset
);

/* Destroys a single VkBuffer pointed to by buffer */
void destroy_buffer(const VulkanCore* core, const VkBuffer* buffer);

#endif // BUFFERS_H
