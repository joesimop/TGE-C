#pragma once

#define GLFW_INCLUDE_VULKAN
#include <stdio.h>
#include <vulkan/vulkan.h>
#include "../include/utils/helpers.h"
#include "global.h"

// Global debug messenger information
VkDebugUtilsMessengerEXT g_debugMessenger;
VkDebugUtilsMessengerCreateInfoEXT debugCreateInfoCreateDestroy;

/// Callback function for the debug messenger
///  @param messageSeverity The severity of the message
///  @param messageType The type of the message
///  @param pCallbackData The callback data
///  @param pUserData The user data
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData
);

/// Sets up the debug messenger
void setup_debug_messenger(VkInstance* instance);

/// Sets constants for the debug messenger
void populate_debug_messenger(VkDebugUtilsMessengerCreateInfoEXT* createInfo);

// Proxy to create/destroy debug extension object
VkResult __create_debug_utils_messenger_ext(
        VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger
);
void __destroy_debug_utils_messenger_ext(VkInstance instance, const VkAllocationCallbacks* pAllocator);
void destroy_debug_messenger(VkInstance instance);
