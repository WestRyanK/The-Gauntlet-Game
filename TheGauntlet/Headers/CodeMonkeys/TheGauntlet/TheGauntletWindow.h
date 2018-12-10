#pragma once

#include "glitter.hpp"

namespace CodeMonkeys::TheGauntlet
{
    class TheGauntletWindow
    {
    private:
        GLFWwindow* window;
        float width;
        float height;

    public:
        TheGauntletWindow(int width, int height, bool fullscreen);
        GLFWwindow* get_window();
        float get_width();
        float get_height();
    };
}