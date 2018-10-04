#pragma once

#include "IControllable.h"

namespace CodeMonkeys::TheGauntlet::Engine::Control
{
    class Controller
    {
    private:
        IControllable controllable;
    public:
        Controller(IControllable controllable);
        virtual void handle_input() = 0;
    };
}