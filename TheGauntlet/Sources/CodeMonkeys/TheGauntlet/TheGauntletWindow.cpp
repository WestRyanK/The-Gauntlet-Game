#include "CodeMonkeys/TheGauntlet/TheGauntletWindow.h"

using CodeMonkeys::TheGauntlet::TheGauntletWindow;

TheGauntletWindow::TheGauntletWindow(int width, int height, bool fullscreen)
{
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = NULL;
    if (fullscreen)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        window = glfwCreateWindow(mode->width, mode->height, "The Gauntlet", glfwGetPrimaryMonitor(), nullptr);
        this->width = mode->width;
        this->height = mode->height;
    }
    else
    {
        window = glfwCreateWindow(width, height, "The Gauntlet", nullptr, nullptr);
        this->width = width;
        this->height = height;
    }

    // Check for Valid Context
    if (window == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        exit(EXIT_FAILURE);
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(window);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    glfwSetWindowPos(window, 0, 0);
    this->window = window;
}

GLFWwindow* TheGauntletWindow::get_window()
{
    return this->window;
}

float TheGauntletWindow::get_width()
{
    return this->width;
}

float TheGauntletWindow::get_height()
{
    return this->height;
}