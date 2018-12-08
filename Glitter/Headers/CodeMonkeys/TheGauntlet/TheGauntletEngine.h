#pragma once

#include "CodeMonkeys/Engine/Engine/GameEngine.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletEngineSettings.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"

using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

namespace CodeMonkeys::TheGauntlet
{
    class TheGauntletEngine: public GameEngine
    {
    private:
        void update_frame(float dt);
        void init_skybox();
        void init_light_and_camera(Ship* camera_parent);
        void setup_course();
        TheGauntletEngineSettings* settings = NULL;

    public:
        TheGauntletEngine(GLFWwindow* window, GLuint width, GLuint height, TheGauntletEngineSettings* settings);
        // TheGauntletEngine(GLFWwindow* window, GLuint width, GLuint height);
        void init();
    };

}