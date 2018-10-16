#include "ILight3D.h"
#include "NIE.h"
#include <sstream>
#include "glitter.hpp"
#include <string>
#include <iostream>

using namespace glm;
using namespace std;
using CodeMonkeys::Engine::Objects::ILight3D;

ILight3D::ILight3D(vec3 color, float strength)
{
    this->color = color;
    this->strength = strength;
}

vec3 ILight3D::get_color()
{
    return this->color;
}

void ILight3D::set_color(vec3 color)
{
    this->color = color;
}

float ILight3D::get_strength()
{
    return this->strength;
}

void ILight3D::set_strength(float strength)
{
    this->strength = strength;
}

string ILight3D::get_uniform_name(string light_type, unsigned int light_index, string property_name)
{
    std::ostringstream ss;
    ss << property_name;
    // ss << "allLights[" << lightIndex << "]." << propertyName;
    std::string uniform_name = ss.str();
    return uniform_name;
}

void ILight3D::add_light_property_3v(ShaderProgram shader, string light_type, unsigned int light_index, string property_name, vec3 property_value)
{
    string uniform_name = ILight3D::get_uniform_name(light_type, light_index, property_name);
    glUniform3fv(glGetUniformLocation(shader, property_name.c_str()), 1, glm::value_ptr(property_value));
}

void ILight3D::add_light_property_1f(ShaderProgram shader, string light_type, unsigned int light_index, string property_name, float property_value)
{
    string uniform_name = ILight3D::get_uniform_name(light_type, light_index, property_name);
    glUniform1f(glGetUniformLocation(shader, property_name.c_str()), property_value);
}