#pragma once

#include "ILight3D.h"

namespace CodeMonkeys::Engine::Objects
{
    class AmbientLight : public ILight3D
    {
    public:
        AmbientLight(vec3 color, float strength);
        virtual void add_light_to_shader(ShaderProgram shader_program);
    };
}
