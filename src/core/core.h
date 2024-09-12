#pragma once

#ifndef CORE_H
#define CORE_H
#include "glfw_init.h"
#include "vulkanInstance.h"
#include "vulkanDebugMessenger.h"


typedef struct {
    GLFWwindow* window;
    VkInstance instance;
} core_t;


///Initializes the engine
/// @return The intilized core to run the game
core_t initCore();
void destroy(core_t* engine);
void run(core_t* engine);



#endif