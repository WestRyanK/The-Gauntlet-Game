#include "CodeMonkeys/TheGauntlet/Control/KeyboardController.h"

using CodeMonkeys::TheGauntlet::Control::KeyboardController;

KeyboardController* KeyboardController::instance = NULL;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W)
    {
        KeyboardController::instance->w_pressed = (action == GLFW_PRESS || action == GLFW_REPEAT);
        printf("%d\n", KeyboardController::instance->w_pressed);
    }
}

KeyboardController::KeyboardController(IControllable* controllable, GLFWwindow* window) : Controller(controllable, window) 
{ 
    instance = this;
    glfwSetKeyCallback(window, key_callback);
}


void KeyboardController::handle_input(float dt)
{
    glfwPollEvents();
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->controllable->control("move_y", -1.0f, dt);
    }
    if (w_pressed)
    {
        this->controllable->control("move_y", 1.0f, dt);
    }
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(this->window, GLFW_KEY_S) == GLFW_RELEASE)
    {
        this->controllable->control("move_z", 0.0f, dt);
    }
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->controllable->control("move_x", -1.0f, dt);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->controllable->control("move_x", 1.0f, dt);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_RELEASE && glfwGetKey(this->window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        this->controllable->control("move_x", 0.0f, dt);
    }

    if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        this->controllable->control("move_z", -1.0f, dt);
    }
    if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        this->controllable->control("move_z", 1.0f, dt);
    }

    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        this->controllable->control("fire_primary", 1, dt);
    }
    // We register firing key releases in the case that we want to make the user press the key
    // each time they fire instead of holding it down.
    else if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        this->controllable->control("fire_primary", 0, dt);
    }
    if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        this->controllable->control("fire_secondary", 1, dt);
    }
    else if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        this->controllable->control("fire_secondary", 0, dt);
    }
}
