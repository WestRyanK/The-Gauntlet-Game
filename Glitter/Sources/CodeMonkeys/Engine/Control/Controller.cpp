#include "CodeMonkeys/Engine/Control/Controller.h"

using CodeMonkeys::Engine::Control::Controller;

Controller::Controller(IControllable* controllable, GLFWwindow* window)
{
    this->controllable = controllable;
    this->window = window;
}