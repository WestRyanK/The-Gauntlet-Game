#pragma once

#include "glitter.hpp"

using namespace glm;

namespace CodeMonkeys::Engine::Objects
{
    class ILight3D
    {
    protected:
        vec3 color;
        float strength;
        void add_light_property();
    public:
        ILight3D(vec3 color, float strength);
        // In order for a shader to use a light, it must add its data to the shader. For each frame, every shader must receive updated values for each light.
        virtual void add_light_to_shader(ShaderProgram shader_program);
        vec3 get_color();
        void set_color(vec3 color);
        float get_strength();
        void set_strength(float strength);
    };
}
