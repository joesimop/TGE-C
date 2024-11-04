#include "buffers.h"

void allocate_buffer(const VulkanCore* core, VkBuffer buffer, VkDeviceMemory* device_memory, VkDeviceSize offset) {


    const VkMemoryRequirements memoryRequirements = get_memory_requirements(core, buffer);

    const VkMemoryAllocateInfo allocInfo = MEMORY_ALLOCATION_INFO(
            size, memoryRequirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
    );

    ASSERT(vkAllocateMemory(core->logicalDevice, &allocInfo, NULL, device_memory) == VK_SUCCESS,
           "Could not allocate memory for buffer.");

    // If we successfully allocate the memory for the buffer, we need to bind it
    // Make sure offset is divisible by alignment
    ASSERT(offset % memoryRequirements.alignment == 0, "Buffer offset not aligned.");

    vkBindBufferMemory(core->logicalDevice, buffer, *device_memory, offset);
}

void fill_buffer(
        const VulkanCore* core, const VkDeviceMemory* device_memory, const size_t size, const void* data,
        const VkDeviceSize offset
) {

    void* copyBuffer;
    vkMapMemory(core->logicalDevice, *device_memory, offset, size, 0, &copyBuffer);
    memcpy(copyBuffer, data, size);
    vkUnmapMemory(core->logicalDevice, *device_memory);
}


void destroy_buffer(const VulkanCore* core, const VkBuffer* buffer) {
    vkDestroyBuffer(core->logicalDevice, *buffer, NULL);
}
