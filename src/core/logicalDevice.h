#pragma once

#include <vulkan/vulkan.h>
#include "physicalDevice.h"
#include "global.h"
/*
Keep in mind:
You can even create multiple logical devices
from the same physical device if you have 
varying requirements.
*/

//Creates the logical device based on a chosen physical device
//Populates the logical device and associated graphics queues
void create_logical_device(VulkanCore* core);

//Sets values for all desired device features
void __init_device_features_all_false(VkPhysicalDeviceFeatures* deviceFeatures);

//Creates the queue create info for the
//logical device based on a chosen physical device
void __populate_queue_info_for_logical_device(QueueFamilyIndices indices, VkDeviceQueueCreateInfo* queueCreateInfo);

//Enables device specific extensions and v. layers
void __enable_device_specific_extensions(VkDeviceCreateInfo* deviceCreateInfo);

//Destroys the logical device
void destroy_logical_device(VkDevice device);