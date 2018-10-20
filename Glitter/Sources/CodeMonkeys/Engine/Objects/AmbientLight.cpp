#include "AmbientLight.h"
#include "NIE.h"

using namespace glm;
using CodeMonkeys::Engine::Objects::AmbientLight;

AmbientLight::AmbientLight(vec3 color, float strength) : CodeMonkeys::Engine::Objects::ILight3D(color, strength)
{
}

void AmbientLight::add_light_to_shader(ShaderProgram* shader, unsigned int light_index)
{
    shader->setUniform(ILight3D::get_uniform_name("ambient", light_index, "color").c_str(), this->color);
    shader->setUniform(ILight3D::get_uniform_name("ambient", light_index, "strength").c_str(), this->strength);
}