#include "vulkanInstance.h"
#include "../include/utils/types.h"
#include "../include/structs/dynamicarray.h"
#include "../include/utils/helpers.h"
#include "global.h"


void InitVulkan(VkInstance *instance) {

    //Check if required validation layers are supported
    if(enableValidationLayers && !checkValidationLayerSupport()) {
        perror("Validation layers requested, but not available!");
    }
    *instance = createVulkanInstance();    
}

VkInstance createVulkanInstance(){
    VkInstance instance;

    VkApplicationInfo appInfo;
    createAppInfo(&appInfo);

    VkInstanceCreateInfo createInfo;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    //Necessary for MoltenSDK on macOS
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    configureExtensions(&createInfo);

    ASSERT(vkCreateInstance(&createInfo, NULL, &instance) == VK_SUCCESS, "Failed to create instance!");

    //NOTE: MAKE SURE EVERYTHING IS WORKING WITH THIS.
    //Freeing my dynamic memory, but could mess with the Instance.
    da_free(createInfo.ppEnabledExtensionNames);

    return instance;
}

void createAppInfo(VkApplicationInfo* appInfo) {

    appInfo->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo->pApplicationName = "Hello Triangle";
    appInfo->applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo->pEngineName = "No Engine";
    appInfo->engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo->apiVersion = VK_API_VERSION_1_0;
    appInfo->pNext = NULL;

}

const char** getRequiredExtensions() {

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    //Create a dynamic array of the required extensions
    DYNAMIC_ARRAY(const char *) allExtenstions = NULL;
    da_init_from_data(allExtenstions, glfwExtensions);

    if (enableValidationLayers) {

        //Add the debug utils extension
        const char** extraDebugUtils = da_push(allExtenstions);
        *extraDebugUtils = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    }

    //Necessary for MoltenSDK on macOS
    const char** portability_enumeration = da_push(allExtenstions);
    *portability_enumeration = VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;
    
    return allExtenstions;
}

void configureExtensions(VkInstanceCreateInfo* createInfo) {

    u32 glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = getRequiredExtensions();

    createInfo->enabledExtensionCount = (u32) da_size(glfwExtensions);
    createInfo->ppEnabledExtensionNames = glfwExtensions;


    if(enableValidationLayers){
        createInfo->enabledLayerCount = ARRAY_SIZE(validationLayers);
        createInfo->ppEnabledLayerNames = validationLayers;

        //Enable debug messenger for create and destroy calls
        // populateDebugMessenger(&debugCreateInfoCreateDestroy);
        // createInfo->pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfoCreateDestroy;

    } else {
        createInfo->enabledLayerCount = 0;
        createInfo->pNext = NULL;
    }

}

bool checkValidationLayerSupport() {

    //Get the layers supported by the Vulkan runtime
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);

    VkLayerProperties availableLayers[layerCount];
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);

    //Check if the layers we want are supported
    for (int i = 0; i < ARRAY_SIZE(validationLayers); i++) {

        //Current Validation Layer we are checking
        const char* layerName = validationLayers[i];
        bool layerFound = false;

        //Go through the Vulkan runtime layers and check for support
        for (int j = 0; j < layerCount; j++) {
            if (strcmp(layerName, availableLayers[j].layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        //Error if the layer is not supported
        ASSERT(layerFound, "\"%s\" validation layer not supported", layerName);
    }

    //All validation layers are supported
    return true;
}