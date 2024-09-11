#include "glfw_init.h"

GLFWwindow* initWindow() {
    glfwInit();

    //WINDOW SETTINGS
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);       //No OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);         //Disable resizing for now

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan window", NULL, NULL);
    ASSERT_NOT_NULL(window);

    return window;
}