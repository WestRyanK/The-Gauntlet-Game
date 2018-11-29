#pragma once

#include "CodeMonkeys/Engine/Engine/GameEngine.h"

using namespace CodeMonkeys::Engine::Engine;

namespace CodeMonkeys::TheGauntlet
{
    class TheGauntletEngine: public GameEngine
    {
    private:
        void update_frame(float dt);
        void init_skybox();
        void init_light_and_camera(Object3D* camera_parent);
        void setup_course();

    public:
        TheGauntletEngine(GLFWwindow* window, GLuint width, GLuint height);
        void init();
    };
}