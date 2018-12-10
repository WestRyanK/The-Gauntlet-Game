#pragma once

#include "glitter.hpp"

namespace CodeMonkeys::TheGauntlet
{
    class TheGauntletWindow
    {
    private:
        GLFWwindow* window;

    public:
        TheGauntletWindow(int width, int height);
        GLFWwindow* get_window();
    };
}