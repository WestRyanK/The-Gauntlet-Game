#include "ILight3D.h"

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