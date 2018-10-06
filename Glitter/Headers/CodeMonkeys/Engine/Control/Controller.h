#pragma once

#include "CodeMonkeys/Engine/Control/IControllable.h"

namespace CodeMonkeys::Engine::Control
{
    class Controller
    {
    private:
        IControllable* controllable = NULL;
    public:
        Controller(IControllable* controllable);
        virtual void handle_input() = 0;
    };
}