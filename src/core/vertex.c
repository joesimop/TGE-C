#include "vertex.h"

const ShaderVertex vertices[3] = {
        {{0.0f, -0.5f}, {0.5f, 0.5f, 0.0f}},
        {{0.5f, 0.5f},  {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

void create_vertex_buffer(const VulkanCore* core, const size_t size, VkBuffer* vertexBuffer) {

    const VkBufferCreateInfo createInfo = VERTEX_BUFFER_CREATE_INFO(size, VK_SHARING_MODE_EXCLUSIVE);

    ASSERT(vkCreateBuffer(core->logicalDevice, &createInfo, NULL, vertexBuffer) == VK_SUCCESS,
           "Couldn't create VkBuffer");
}
