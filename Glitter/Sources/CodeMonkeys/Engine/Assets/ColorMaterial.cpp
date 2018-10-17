#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"

using CodeMonkeys::Engine::Assets::ColorMaterial;
using namespace CodeMonkeys::Engine::Assets;


ColorMaterial::ColorMaterial(ShaderProgram* shader, bool use_phong_highlight, float phong_exponent, vec3 phong_color, vec3 color) : Material(shader, use_phong_highlight, phong_exponent, phong_color)
{
    this->color = color;
}

void ColorMaterial::apply_material_to_shader()
{
    Material::apply_material_to_shader();

    this->shader->setUniform("object_color", this->color);
}