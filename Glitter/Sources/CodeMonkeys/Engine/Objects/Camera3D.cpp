#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "glitter.hpp"
#include "NIE.h"

using CodeMonkeys::Engine::Objects::Camera3D;

Camera3D::Camera3D() : Object3D(NULL)
{

}

vec4 Camera3D::get_look_at()
{
    return this->look_at;
}

void Camera3D::set_look_at(vec4 look_at)
{
    this->look_at = look_at;
}

vec4 Camera3D::get_up()
{
    return this->up;
}

void Camera3D::set_up(vec4 up)
{
    this->up = up;
}

void Camera3D::update_shader_with_camera(ShaderProgram shader)
{
    throw NotImplementedException("Camera3D::update_shader_with_camera");
}