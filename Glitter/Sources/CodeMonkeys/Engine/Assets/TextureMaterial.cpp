#include "CodeMonkeys/Engine/Assets/TextureMaterial.h"

using CodeMonkeys::Engine::Assets::TextureMaterial;
using namespace CodeMonkeys::Engine::Assets;

TextureMaterial::TextureMaterial(ShaderProgram* shader, bool use_phong_highlight, float phong_exponent, vec3 phong_color, Texture* texture) : Material(shader, use_phong_highlight, phong_exponent, phong_color)
{
    this->texture = texture;
}

void TextureMaterial::apply_material_to_shader()
{
    Material::apply_material_to_shader();


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture->get_texture_id());
    this->shader->setUniform("texture_0", 0);
}