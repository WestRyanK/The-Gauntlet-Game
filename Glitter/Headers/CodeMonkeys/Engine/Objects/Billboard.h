#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"
#include <string>

using namespace std;
using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::Engine::Objects
{
    class Billboard : public PhysicalObject3D
    {
    private:
        static ShaderProgram* billboard_shader;
        static GLuint* billboard_vao;
        static void init_billboard_class();

        Texture* billboard_texture;
        float width;
        float height;
    public:
        Billboard(std::string name, Texture* billboard_texture, float width, float height);

        virtual void draw(mat4 total_transform, ShaderProgram* shader);
        static ShaderProgram* get_shader();
        void update(float dt);
    };
}