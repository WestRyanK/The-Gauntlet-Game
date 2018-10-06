#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/ILight3D.h"

using namespace glm;

namespace CodeMonkeys::Engine::Objects
{
    class DirectionalLight : public ILight3D
    {
    private:
        vec3 direction;
    public:
        DirectionalLight(vec3 color, float strength, vec3 direction);
        vec3 get_direction();
        void set_direction(vec3 direction);
        virtual void add_light_to_shader(ShaderProgram shader_program);
    };
}