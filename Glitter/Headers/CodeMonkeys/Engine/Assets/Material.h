#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"

using namespace glm;

namespace CodeMonkeys::Engine::Assets
{
    class Material
    {
    protected:
        vec3 phong_color;
        float phong_exponent;
        bool use_phong_highlight = true;
        ShaderProgram* shader;
        void set_material_type_id(unsigned int material_type_id);
    public:
        Material(ShaderProgram* shader, bool use_phong_highlight, float phong_exponent, vec3 phong_color);
        vec3 get_phong_color();
        float get_phong_exponent();
        bool get_use_phong_highlight();
        virtual Material* clone() = 0;
        ShaderProgram* get_shader();
        virtual void apply_material_to_shader();
        // This must be an id unique to the Material type;
        // Lets make ColorMaterial = 1 and TextureMaterial = 2;
        virtual int get_material_type_id() = 0;
    };
}