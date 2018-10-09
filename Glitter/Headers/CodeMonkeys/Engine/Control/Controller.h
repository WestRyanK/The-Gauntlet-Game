#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Control/IControllable.h"

namespace CodeMonkeys::Engine::Control
{
    class Controller
    {
    protected:
        IControllable* controllable = NULL;
        GLFWwindow* window = NULL;
    public:
        Controller(IControllable* controllable, GLFWwindow* window);
        virtual void handle_input(float dt) = 0;
    };
}