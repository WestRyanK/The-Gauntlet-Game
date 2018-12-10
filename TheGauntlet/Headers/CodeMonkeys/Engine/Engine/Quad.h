#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
// #include "CodeMonkeys/Engine/Assets/Texture.h"

using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::Engine::Engine
{
    class Quad
    {
    private:
        static ShaderProgram* quad_shader;
        static GLuint quad_vao;
        static void init();

    protected:
        GLuint quad_texture_id;
        vec2 position;
        vec2 size;

    public:
        Quad(vec2 position, vec2 size);
        virtual void draw();
        virtual void update(float dt);
        void set_texture(GLuint texture);
        GLuint get_texture();
    };
}