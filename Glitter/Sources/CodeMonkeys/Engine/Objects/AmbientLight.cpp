#include "AmbientLight.h"
#include "NIE.h"

using namespace glm;
using CodeMonkeys::Engine::Objects::AmbientLight;

AmbientLight::AmbientLight(vec3 color, float strength) : CodeMonkeys::Engine::Objects::ILight3D(color, strength)
{
}

void AmbientLight::add_light_to_shader(ShaderProgram shader_program)
{
    throw NotImplementedException("AmbientLight::add_light_to_shader");
}