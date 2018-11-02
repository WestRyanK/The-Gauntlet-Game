#pragma once

#include "CodeMonkeys/Engine/Engine/FrameBufferRenderer.h"
#include "glitter.hpp"

using namespace glm;

namespace CodeMonkeys::Engine::Engine
{
    class Renderer3D : public FrameBufferRenderer
    {
    private:
        float camera_spacing;

        Camera3D* create_second_camera(Camera3D* camera);
    public:
        Renderer3D(GLFWwindow* window, int width, int height, float camera_spacing);
        void render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox);
    };
}