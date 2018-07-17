
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "playground/window.h"

void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error : %s\n", description);
}

void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* InitWindowContext(GLFWwindow *window)
{
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) {
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!window) {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        return NULL;
    }

    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, Framebuffer_Size_Callback);

    return window;
}

