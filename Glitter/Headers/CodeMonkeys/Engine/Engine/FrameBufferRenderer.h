#pragma once

#include "CodeMonkeys/Engine/Engine/Renderer.h"

namespace CodeMonkeys::Engine::Engine
{
    class FrameBufferRenderer : public Renderer
    {
    private:
        void create_output_quad();
        GLuint quad_vao;
        GLuint quad_texture_id;
        ShaderProgram* quad_shader;

    protected:
        GLuint frame_buffer;
        GLuint rendered_texture;

        void create_frame_buffer(GLuint width, GLuint height, GLuint& frame_buffer, GLuint& rendered_texture);
        void set_frame_buffer(GLuint frame_buffer, GLuint x, GLuint y, GLuint width, GLuint height);
        void draw_frame_buffer(GLuint rendered_texture);
    
    public:
        FrameBufferRenderer(GLFWwindow* window, GLuint width, GLuint height);
        virtual void render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox);

    };
}