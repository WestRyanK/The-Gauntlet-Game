#pragma once
#include "CodeMonkeys/Engine/Control/Controller.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"

using namespace CodeMonkeys::Engine::Control;

namespace CodeMonkeys::TheGauntlet::Control
{
    class KeyboardController : public Controller
    {
    private:
    public:
        void handle_input(float dt);
        KeyboardController(IControllable* controllable, GLFWwindow* window);
    };
}