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
        GLuint quad_vao;
        GLuint quad_texture_id;

    public:
        Quad(float x, float y, float width, float height);
        void draw(GLuint texture);
    };
}