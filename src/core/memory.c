#include "memory.h"

VkMemoryRequirements get_memory_requirements(const VulkanCore* core, VkBuffer buffer) {
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(core->logicalDevice, buffer, &memoryRequirements);

    return memoryRequirements;
}

u32 find_memory_type(const VulkanCore* core, const u32 typeFilter, const VkMemoryPropertyFlags properties) {

    // Get available memory types
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(core->physicalDevice, &memoryProperties);

    for (u32 i = 0; i < memoryProperties.memoryTypeCount; i++) {
        // ReSharper disable once CppRedundantParentheses
        // ensure typeFilter and memory types are matched.
        if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    // If we didn't find anything, we need to error.
    ASSERT(true == false, "Could not find suitable memory type.");
}
