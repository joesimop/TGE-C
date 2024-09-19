#include "physicalDevice.h"

void pick_physical_device(VulkanCore* core) {

    //Query vulkan for the number of devices
    u32 deviceCount = 0;
    vkEnumeratePhysicalDevices(core->instance, &deviceCount, NULL);

    ASSERT(deviceCount != 0, "Failed to find GPUs with Vulkan support!");

    //If there are devices, populate them into a dynamic array
    DYNAMIC_ARRAY(VkPhysicalDevice) devices = NULL;
    da_init(devices, deviceCount);
    vkEnumeratePhysicalDevices(core->instance, &deviceCount, devices);

    //Find one that is suitable and break.
    core->physicalDevice = VK_NULL_HANDLE;
    for (int i = 0; i < deviceCount; i++) {
        if (__is_device_suitable(devices[i], core)) {
            core->physicalDevice = devices[i];
            break;
        }
    }

    ASSERT(core->physicalDevice != VK_NULL_HANDLE, "Failed to find a suitable GPU!");

    //Free the dynamic array
    da_free(devices);
}

bool __is_device_suitable(VkPhysicalDevice device, VulkanCore* core) {
    
    //First get the properties of the device
    //This includes the name, type, and supported Vulkan version
    // VkPhysicalDeviceProperties deviceProperties;
    // vkGetPhysicalDeviceProperties(device, &deviceProperties);

    // //Next get the features of the device
    // //This is optional features like geometry shaders and texture compression
    // VkPhysicalDeviceFeatures deviceFeatures;
    // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    //Make sure there are supported queue families
    QueueFamilyIndices indices = __find_queue_families(device, core->surface);

    //Check if the device supports the required extensions
    bool extensionsSupported = __check_device_extension_support(device);

    //Check if there is a valid interface for the swap chain and surface
    bool swapChainSupported = false;
    if(extensionsSupported){
        SwapChainSupportDetails details = query_swap_chain_specs(device, core->surface);
        swapChainSupported = da_size(details.formats) > 0 && da_size(details.presentModes) > 0;

        //Set the swap chain details in core
        core->swapChainDetails = details;
    }

    //Set them here, if they are invalid, ASSERT outside of this function will catch it
    core->indices = indices;

    //If all three, we are good to go
    return __is_valid_queue_family(indices) && extensionsSupported && swapChainSupported;
}

bool __check_device_extension_support(VkPhysicalDevice device) {
    u32 extensionCount;
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);

    DYNAMIC_ARRAY(VkExtensionProperties) availableExtensions = NULL;
    da_init(availableExtensions, extensionCount);

    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, availableExtensions);

    //Check if all the required extensions are supported by the device
    bool supported = true;
    for (int i = 0; i < ARRAY_SIZE(DEVICE_EXTENSIONS); i++) {
        bool found = false;
        for (int j = 0; j < extensionCount; j++) {
            if (strcmp(DEVICE_EXTENSIONS[i], availableExtensions[j].extensionName) == 0) {
                found = true;
                break;
            }
        }
        if (!found) { supported = false; break; }
    }
    da_free(availableExtensions);
    return supported;
}

QueueFamilyIndices __find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface) {

    QueueFamilyIndices families;

    //Get the number of queue families
    u32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);


    //If there are queue families, populate them into a dynamic array
    if (queueFamilyCount != 0) {

        DYNAMIC_ARRAY(VkQueueFamilyProperties) queueFamilies = NULL;
        da_init(queueFamilies, queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

        //Find a queue family that supports graphics
        VkBool32 presentSupport = false;
        for (int i = 0; i < queueFamilyCount; i++) {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {

                //Check if the queue family supports presenting
                vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

                //Only return value if both surface and graphics support the queue family
                if (presentSupport) {
                    set_opt(families.graphicsFamily, i);
                    set_opt(families.presentFamily, i);
                    break;
                }
            }
        }
        da_free(queueFamilies);
    }
    return families;
}