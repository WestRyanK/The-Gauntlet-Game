#pragma once

#include "CodeMonkeys/Engine/Engine/Renderer.h"
#include "CodeMonkeys/Engine/Engine/Quad.h"

namespace CodeMonkeys::Engine::Engine
{
    class FrameBufferRenderer : public Renderer
    {
    private:
        Quad* quad;
        // Texture* tex;

    protected:
        GLuint frame_buffer;
        GLuint rendered_texture;

        void create_frame_buffer(GLuint width, GLuint height, GLuint& frame_buffer, GLuint& rendered_texture);
        void draw_frame_buffer(GLuint rendered_texture);
    
    public:
        FrameBufferRenderer(GLFWwindow* window, GLuint width, GLuint height);
        virtual void render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox, set<Quad*> quads);

    };
}