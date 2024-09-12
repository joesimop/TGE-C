#include "glfw_init.h"

void init_window(GLFWwindow** window) {
    glfwInit();

    //WINDOW SETTINGS
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);       //No OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);         //Disable resizing for now

    *window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan window", NULL, NULL);
    ASSERT_NOT_NULL(window);
}