#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Assets/Material.h"

using namespace glm;

namespace CodeMonkeys::Engine::Assets
{
    class ColorMaterial : public Material
    {
    protected:
        vec3 color;
        void apply_color_to_shader();
    public:
        ColorMaterial(ShaderProgram* shader, bool use_phong_highlight, float phong_exponent, vec3 phong_color, vec3 color);
        vec3 get_color();
        void set_color(vec3 color);
        virtual void apply_material_to_shader();
        virtual int get_material_type_id() { return 1; };
    };
}