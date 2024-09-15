#include "physicalDevice.h"

void pick_physical_device(VkInstance instance, VkSurfaceKHR surface, VkPhysicalDevice *physicalDevice) {

    //Query vulkan for the number of devices
    u32 deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

    ASSERT(deviceCount != 0, "Failed to find GPUs with Vulkan support!");

    //If there are devices, populate them into a dynamic array
    DYNAMIC_ARRAY(VkPhysicalDevice) devices = NULL;
    da_init(devices, deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    //Find one that is suitable and break.
    for (int i = 0; i < deviceCount; i++) {
        if (__is_device_suitable(devices[i], surface)) {
            *physicalDevice = devices[i];
            break;
        }
    }



    ASSERT(*physicalDevice != VK_NULL_HANDLE, "Failed to find a suitable GPU!");

    //Free the dynamic array
    da_free(devices);
}

bool __is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    
    //First get the properties of the device
    //This includes the name, type, and supported Vulkan version
    // VkPhysicalDeviceProperties deviceProperties;
    // vkGetPhysicalDeviceProperties(device, &deviceProperties);

    // //Next get the features of the device
    // //This is optional features like geometry shaders and texture compression
    // VkPhysicalDeviceFeatures deviceFeatures;
    // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    QueueFamilyIndices indices = __find_queue_families(device, surface);

    return __is_valid_queue_family(indices);
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
    }
    
    return families;
}