#pragma once

#include "CodeMonkeys/Engine/Engine/FrameBufferRenderer.h"
#include "CodeMonkeys/Engine/Engine/Quad.h"
#include "glitter.hpp"

using namespace glm;

namespace CodeMonkeys::Engine::Engine
{
    class Renderer3D : public FrameBufferRenderer
    {
    private:
        float camera_spacing;
        Quad* quads[2];
        GLuint frame_buffers[2];
        GLuint rendered_textures[2];

        vector<Camera3D*> create_3d_cameras(Camera3D* camera);
    public:
        Renderer3D(GLFWwindow* window, int width, int height, float camera_spacing);
        void render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox, set<Quad*> quads);
    };
}