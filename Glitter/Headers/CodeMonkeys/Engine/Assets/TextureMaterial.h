#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"

using namespace glm;

namespace CodeMonkeys::Engine::Assets
{
    class TextureMaterial : public ColorMaterial
    {
    protected:
        Texture* texture = NULL;
    public:
        TextureMaterial(ShaderProgram* shader, bool use_phong_highlight, float phong_exponent, vec3 phong_color, vec3 color, Texture* texture);
        TextureMaterial(ShaderProgram* shader, bool use_phong_highlight, float phong_exponent, vec3 phong_color, Texture* texture);
        Texture* get_texture();
        virtual void apply_material_to_shader();
        virtual int get_material_type_id() { return 2; };
    };
}