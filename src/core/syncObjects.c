#include "syncObjects.h"

#define FRAMES_IN_FLIGHT 2

void create_sync_objects(RenderState* renderState) {


    ASSERT(FRAMES_IN_FLIGHT <= MAX_FRAMES_IN_FLIGHT, "Frames in flight must be less than max frames in flight");

    VkSemaphoreCreateInfo semaphoreInfo;
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreInfo.pNext = NULL;
    semaphoreInfo.flags = 0;

    VkFenceCreateInfo fenceInfo;
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.pNext = NULL;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
        ASSERT(vkCreateSemaphore(renderState->core->logicalDevice, &semaphoreInfo, NULL, &renderState->cb_waitSemaphores[i]) == VK_SUCCESS &&
               vkCreateSemaphore(renderState->core->logicalDevice, &semaphoreInfo, NULL, &renderState->signalSemaphores[i]) == VK_SUCCESS &&
               vkCreateFence(renderState->core->logicalDevice, &fenceInfo, NULL, &renderState->inFlightFences[i]) == VK_SUCCESS, "Failed to create sync objects");
    }


}


void destroy_sync_objects(RenderState* renderState) {
    for (int i = 0; i < FRAMES_IN_FLIGHT; i++){
        vkDestroySemaphore(renderState->core->logicalDevice, renderState->cb_waitSemaphores[i], NULL);
        vkDestroySemaphore(renderState->core->logicalDevice, renderState->signalSemaphores[i], NULL);
        vkDestroyFence(renderState->core->logicalDevice, renderState->inFlightFences[i], NULL);
    }
}