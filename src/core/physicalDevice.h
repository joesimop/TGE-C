#pragma once

#include <vulkan/vulkan.h>
#include "global.h"
#include "swapChain.h"
#include "../include/structs/dynamicarray.h"
#include "../include/utils/types.h"



typedef struct {
    opt_u32 graphicsFamily;
    opt_u32 presentFamily;
} QueueFamilyIndices;

static bool __is_valid_queue_family(QueueFamilyIndices indices){
    return has_value(indices.graphicsFamily) && has_value(indices.presentFamily);
}


//Enumerates and picks the physical device based on __is_device_suitable()
void pick_physical_device(VkInstance instance,VkSurfaceKHR surface, VkPhysicalDevice *physicalDevice);

//Returns true if the device is suitable for the application
//Right now, just returns true, implementation depends on the application
bool __is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR surface);

//Returns true if the device supports all the required extensions for the device
bool __check_device_extension_support(VkPhysicalDevice device);

//Finds the queue families for the device
QueueFamilyIndices __find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface);