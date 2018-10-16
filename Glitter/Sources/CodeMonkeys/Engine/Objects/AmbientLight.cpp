#include "AmbientLight.h"
#include "NIE.h"

using namespace glm;
using CodeMonkeys::Engine::Objects::AmbientLight;

AmbientLight::AmbientLight(vec3 color, float strength) : CodeMonkeys::Engine::Objects::ILight3D(color, strength)
{
}

void AmbientLight::add_light_to_shader(ShaderProgram shader_program, unsigned int light_index)
{
    string type = "ambient";
    string color = "color";
    string strength = "strength";
    ILight3D::add_light_property_3v(shader_program, type, light_index, color, this->color);
    ILight3D::add_light_property_1f(shader_program, type, light_index, strength, this->strength);
}