#ifndef MEMORY_H
#define MEMORY_H

#include "global.h"

/* Standardized init of VkMemoryAllocateInfo struct */
#define MEMORY_ALLOCATION_INFO(__size, __mem_req, ___mem_properties)                                                   \
    {.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,                                                                  \
     .allocationSize = (__mem_req).size,                                                                               \
     .memoryTypeIndex = find_memory_type(core, (__mem_req).memoryTypeBits, (___mem_properties)),                       \
     .pNext = NULL}

/* Returns the memory requirements for allocating a buffer */
VkMemoryRequirements get_memory_requirements(const VulkanCore* core, VkBuffer buffer);

/* Finds a memory type give the memoryTypeBits of a VKMemoryRequirements struct
   and properties we want the memory to have */
u32 find_memory_type(const VulkanCore* core, u32 typeFilter, VkMemoryPropertyFlags properties);

#endif // MEMORY_H
