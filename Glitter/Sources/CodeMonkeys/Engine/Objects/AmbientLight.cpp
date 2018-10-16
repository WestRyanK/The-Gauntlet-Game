#include "AmbientLight.h"
#include "NIE.h"

using namespace glm;
using CodeMonkeys::Engine::Objects::AmbientLight;

AmbientLight::AmbientLight(vec3 color, float strength) : CodeMonkeys::Engine::Objects::ILight3D(color, strength)
{
}

void AmbientLight::add_light_to_shader(ShaderProgram shader_program)
{
    ILight3D::add_light_property_3v(shader_program, "ambient", 0, "ambient_color", this->color);
    ILight3D::add_light_property_1f(shader_program, "ambient", 0, "ambient_strength", this->strength);
}