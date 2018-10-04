#pragma once

#include <string>
using namespace std;

namespace CodeMonkeys::TheGauntlet::Engine::Control
{
    class IControllable
    {
    public:
        virtual void control(std::string control_name, float value_a, float value_b) = 0;
        virtual void control(std::string control_name, float value) = 0;
        virtual void control(std::string control_name, int value) = 0;
    };
}