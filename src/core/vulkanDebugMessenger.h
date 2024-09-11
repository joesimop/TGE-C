#pragma once

#ifndef VULKAN_DEBUG_MESSENGER_H
#define VULKAN_DEBUG_MESSENGER_H
#define GLFW_INCLUDE_VULKAN
#include "global.h"
#include "../include/utils/helpers.h"
#include <vulkan/vulkan.h>
#include <stdio.h>

//Global debug messenger information
VkDebugUtilsMessengerEXT debugMessenger;
VkDebugUtilsMessengerCreateInfoEXT debugCreateInfoCreateDestroy;

///Callback function for the debug messenger
/// @param messageSeverity The severity of the message
/// @param messageType The type of the message
/// @param pCallbackData The callback data
/// @param pUserData The user data
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
);

///Sets up the debug messenger
void setupDebugMessenger(VkInstance *instance);

///Sets constants for the debug messenger
void populateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT *createInfo);

//Proxy to create/destroy debug extension object 
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, const VkAllocationCallbacks* pAllocator);
void DestroyDebugMessenger(VkInstance instance);

#endif