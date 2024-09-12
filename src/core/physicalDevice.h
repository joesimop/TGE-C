#pragma once

#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H

#include <vulkan/vulkan.h>
#include "../include/utils/types.h"
#include "../include/utils/helpers.h"
#include "../include/structs/dynamicarray.h"


typedef struct {
    opt_u32 graphicsFamily;
} QueueFamilyIndices;


//Enumerates and picks the physical device based on __is_device_suitable()
void pick_physical_device(VkInstance *instance,VkPhysicalDevice *physicalDevice);

//Returns true if the device is suitable for the application
//Right now, just returns true, implementation depends on the application
bool __is_device_suitable(VkPhysicalDevice device);

//Finds the queue families for the device
QueueFamilyIndices __find_queue_families(VkPhysicalDevice device);

#endif