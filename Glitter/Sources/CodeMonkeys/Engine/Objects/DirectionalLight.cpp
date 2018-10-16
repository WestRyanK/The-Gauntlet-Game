#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/DirectionalLight.h"
#include "CodeMonkeys/Engine/Objects/ILight3D.h"
#include "NIE.h"

using namespace glm;
using namespace CodeMonkeys::Engine::Objects;
using CodeMonkeys::Engine::Objects::DirectionalLight;

DirectionalLight::DirectionalLight(vec3 color, float strength, vec3 direction) : ILight3D(color, strength)
{
    this->direction = direction;
}

vec3 DirectionalLight::get_direction()
{
    return this->direction;
}

void DirectionalLight::set_direction(vec3 direction)
{
    this->direction = direction;
}

void DirectionalLight::add_light_to_shader(ShaderProgram shader_program, unsigned int light_index)
{
    ILight3D::add_light_property_3v(shader_program, "directional", light_index, "color", this->color);
    ILight3D::add_light_property_1f(shader_program, "directional", light_index, "strength", this->strength);
    ILight3D::add_light_property_3v(shader_program, "directional", light_index, "direction", this->direction);
}