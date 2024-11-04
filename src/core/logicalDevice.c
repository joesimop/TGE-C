#include "logicalDevice.h"

void create_logical_device(VulkanCore* core) {


    VkDeviceQueueCreateInfo queueCreateInfo;
    __populate_queue_info_for_logical_device(core->indices, &queueCreateInfo);

    // Specifiy the device features that will be used,
    // for now, we will just use the default features
    //(might want to pass as a parameter to both physical and logical)
    VkPhysicalDeviceFeatures deviceFeatures;
    __init_device_features_all_false(&deviceFeatures);

    VkDeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos =
            &queueCreateInfo;                  // Can be multiple if multiple queues returned by __find_queue_families()
    deviceCreateInfo.queueCreateInfoCount = 1; // Number of queue families returned by __find_queue_families()
    deviceCreateInfo.flags = 0;
    deviceCreateInfo.pNext = NULL;

    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    __enable_device_specific_extensions(&deviceCreateInfo);

    ASSERT(vkCreateDevice(core->physicalDevice, &deviceCreateInfo, NULL, &core->logicalDevice) == VK_SUCCESS,
           "Failed to create logical device!");

    // Populate the graphics queue from the logical device
    vkGetDeviceQueue(core->logicalDevice, queueCreateInfo.queueFamilyIndex, 0, &core->graphicsQueue);
    vkGetDeviceQueue(core->logicalDevice, core->indices.presentFamily.value, 0, &core->presentQueue);

    // Free data
    da_free(deviceCreateInfo.ppEnabledExtensionNames);
}

void __populate_queue_info_for_logical_device(QueueFamilyIndices indices, VkDeviceQueueCreateInfo* queueCreateInfo) {

    ASSERT(__is_valid_queue_family(indices),
           "Failed to find a suitable queue families for surface and/or physical device!");

    // Right now, with the __find_queue_families() function, the graphics and present families should be the same.
    ASSERT(indices.graphicsFamily.value == indices.presentFamily.value,
           "Graphics and Present queue families are not the same!");
    queueCreateInfo->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo->queueFamilyIndex = indices.graphicsFamily.value;
    queueCreateInfo->queueCount = 1;
    queueCreateInfo->flags = 0;
    queueCreateInfo->pNext = NULL;

    /*
    Vulkan lets you assign priorities to queues to
    influence the scheduling of command buffer execution using
    floating point numbers between 0.0 and 1.0.
    This is required even if there is only a single queue
    */
    float queuePriority = 1.0f; // the UPMOST priority
    queueCreateInfo->pQueuePriorities = &queuePriority;
}

void __enable_device_specific_extensions(VkDeviceCreateInfo* deviceCreateInfo) {

    // Enable extensions and v. layers that are device specific
    DYNAMIC_ARRAY(const char*) deviceSpecificExtensions = NULL;
    da_init(deviceSpecificExtensions, 2);
    *da_push(deviceSpecificExtensions) = VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME;

    // Iterate through the required device extensions and add them
    for (int i = 0; i < ARRAY_SIZE(DEVICE_EXTENSIONS); i++) {
        *da_push(deviceSpecificExtensions) = DEVICE_EXTENSIONS[i];
    }

    deviceCreateInfo->enabledExtensionCount = da_size(deviceSpecificExtensions);
    deviceCreateInfo->ppEnabledExtensionNames = deviceSpecificExtensions;

    if (ENABLE_VALIDATION_LAYERS) {
        deviceCreateInfo->enabledLayerCount = ARRAY_SIZE(VALIDATION_LAYERS);
        deviceCreateInfo->ppEnabledLayerNames = VALIDATION_LAYERS;
    } else {
        deviceCreateInfo->enabledLayerCount = 0;
    }
}

void destroy_logical_device(VkDevice device) { vkDestroyDevice(device, NULL); }

// Sets all values in the device features to false
void __init_device_features_all_false(VkPhysicalDeviceFeatures* deviceFeatures) {
    deviceFeatures->robustBufferAccess = VK_FALSE;
    deviceFeatures->fullDrawIndexUint32 = VK_FALSE;
    deviceFeatures->imageCubeArray = VK_FALSE;
    deviceFeatures->independentBlend = VK_FALSE;
    deviceFeatures->geometryShader = VK_FALSE;
    deviceFeatures->tessellationShader = VK_FALSE;
    deviceFeatures->sampleRateShading = VK_FALSE;
    deviceFeatures->dualSrcBlend = VK_FALSE;
    deviceFeatures->logicOp = VK_FALSE;
    deviceFeatures->multiDrawIndirect = VK_FALSE;
    deviceFeatures->drawIndirectFirstInstance = VK_FALSE;
    deviceFeatures->depthClamp = VK_FALSE;
    deviceFeatures->depthBiasClamp = VK_FALSE;
    deviceFeatures->fillModeNonSolid = VK_FALSE;
    deviceFeatures->depthBounds = VK_FALSE;
    deviceFeatures->wideLines = VK_FALSE;
    deviceFeatures->largePoints = VK_FALSE;
    deviceFeatures->alphaToOne = VK_FALSE;
    deviceFeatures->multiViewport = VK_FALSE;
    deviceFeatures->samplerAnisotropy = VK_FALSE;
    deviceFeatures->textureCompressionETC2 = VK_FALSE;
    deviceFeatures->textureCompressionASTC_LDR = VK_FALSE;
    deviceFeatures->textureCompressionBC = VK_FALSE;
    deviceFeatures->occlusionQueryPrecise = VK_FALSE;
    deviceFeatures->pipelineStatisticsQuery = VK_FALSE;
    deviceFeatures->vertexPipelineStoresAndAtomics = VK_FALSE;
    deviceFeatures->fragmentStoresAndAtomics = VK_FALSE;
    deviceFeatures->shaderTessellationAndGeometryPointSize = VK_FALSE;
    deviceFeatures->shaderImageGatherExtended = VK_FALSE;
    deviceFeatures->shaderStorageImageExtendedFormats = VK_FALSE;
    deviceFeatures->shaderStorageImageMultisample = VK_FALSE;
    deviceFeatures->shaderStorageImageReadWithoutFormat = VK_FALSE;
    deviceFeatures->shaderStorageImageWriteWithoutFormat = VK_FALSE;
    deviceFeatures->shaderUniformBufferArrayDynamicIndexing = VK_FALSE;
    deviceFeatures->shaderSampledImageArrayDynamicIndexing = VK_FALSE;
    deviceFeatures->shaderStorageBufferArrayDynamicIndexing = VK_FALSE;
    deviceFeatures->shaderStorageImageArrayDynamicIndexing = VK_FALSE;
    deviceFeatures->shaderClipDistance = VK_FALSE;
    deviceFeatures->shaderCullDistance = VK_FALSE;
    deviceFeatures->shaderFloat64 = VK_FALSE;
    deviceFeatures->shaderInt64 = VK_FALSE;
    deviceFeatures->shaderInt16 = VK_FALSE;
    deviceFeatures->shaderResourceResidency = VK_FALSE;
    deviceFeatures->shaderResourceMinLod = VK_FALSE;
    deviceFeatures->sparseBinding = VK_FALSE;
    deviceFeatures->sparseResidencyBuffer = VK_FALSE;
    deviceFeatures->sparseResidencyImage2D = VK_FALSE;
    deviceFeatures->sparseResidencyImage3D = VK_FALSE;
    deviceFeatures->sparseResidency2Samples = VK_FALSE;
    deviceFeatures->sparseResidency4Samples = VK_FALSE;
    deviceFeatures->sparseResidency8Samples = VK_FALSE;
    deviceFeatures->sparseResidency16Samples = VK_FALSE;
    deviceFeatures->sparseResidencyAliased = VK_FALSE;
    deviceFeatures->variableMultisampleRate = VK_FALSE;
    deviceFeatures->inheritedQueries = VK_FALSE;
}
