#pragma once

#include "glitter.hpp"
#include <string>

using namespace std;
using namespace glm;

namespace CodeMonkeys::Engine::Objects
{
    class ILight3D
    {
    protected:
        vec3 color;
        float strength;
        static string get_uniform_name(string light_type, unsigned int light_index, string property_name);
        static void add_light_property_3v(ShaderProgram shader, string light_type, unsigned int light_index, string property_name, vec3 property_value);
        static void add_light_property_1f(ShaderProgram shader, string light_type, unsigned int light_index, string property_name, float property_value);
    public:
        ILight3D(vec3 color, float strength);
        // In order for a shader to use a light, it must add its data to the shader. For each frame, every shader must receive updated values for each light.
        virtual void add_light_to_shader(ShaderProgram shader_program) = 0;
        vec3 get_color();
        void set_color(vec3 color);
        float get_strength();
        void set_strength(float strength);
    };
}
