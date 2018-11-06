#pragma once

#include "CodeMonkeys/Engine/Engine/GameEngine.h"

using namespace CodeMonkeys::Engine::Engine;

namespace CodeMonkeys::TheGauntlet
{
    class TheGauntletEngine: public GameEngine
    {
    private:
        void update_frame(float dt);

    public:
        TheGauntletEngine(GLFWwindow* window, GLuint width, GLuint height);
        void init();
    };
}