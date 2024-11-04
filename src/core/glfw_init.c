#include "glfw_init.h"

void init_window(GLFWwindow** window, RenderState* renderState) {
    glfwInit();

    // WINDOW SETTINGS
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);    // Enable resizing

    *window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan window", NULL, NULL);
    ASSERT_NOT_NULL(window);

    glfwSetWindowUserPointer(*window, renderState);
    glfwSetFramebufferSizeCallback(*window, frame_buffer_resize_callback);
}

static void frame_buffer_resize_callback(GLFWwindow* window, int width, int height) {
    RenderState* renderState = glfwGetWindowUserPointer(window);
    renderState->frameBufferResized = true;
}
