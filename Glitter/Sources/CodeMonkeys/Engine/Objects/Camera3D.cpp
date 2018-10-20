#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "glitter.hpp"
#include "NIE.h"

using namespace glm;
using CodeMonkeys::Engine::Objects::Camera3D;

Camera3D::Camera3D() : Object3D(NULL, "Camera")
{
    this->look_at = vec3(0.0f, 0.0f, 0.0f);
    this->position = vec3(0.0f, 0.0f, 20.0f);
    // TODO: Don't hardcode window size.
    this->perspective_projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
}

vec3 Camera3D::get_look_at()
{
    return this->look_at;
}

void Camera3D::set_look_at(vec3 look_at)
{
    this->look_at = look_at;
}

vec3 Camera3D::get_up()
{
    return this->up;
}

void Camera3D::set_up(vec3 up)
{
    this->up = up;
}

void Camera3D::update_shader_with_camera(ShaderProgram* shader)
{
    mat4 view = glm::lookAt(this->position, this->look_at, this->up);

    shader->setUniform("view_transform", view);
    shader->setUniform("projection_transform", this->perspective_projection);
    shader->setUniform("camera_position", this->position);
}

void Camera3D::control(std::string control_name, float value, float dt)
{
    const float velocity = 10.0f;
    const float angular_velocity = 1.0f;
    vec3 forward = glm::normalize(this->look_at - this->position);
    vec3 sideways = -glm::normalize(glm::cross(this->up, this->look_at - this->position));
    if (control_name == "move_x")
    {
        this->position += sideways * dt * value * velocity;
        this->look_at += sideways * dt * value * velocity;
    }
    if (control_name == "move_y")
    {
        this->position.y += value * dt * velocity;
        this->look_at.y += value * dt * velocity;
    }
    if (control_name == "move_z")
    {
        this->position += forward * dt * value * velocity;
        this->look_at += forward * dt * value * velocity;
    }
    if (control_name == "rotate_y")
    {
        mat4 transform;
        transform = glm::rotate(transform, value * glm::radians(angular_velocity), this->up);

        vec4 rotate = vec4(forward.x, forward.y, forward.z, 1.0f) * transform;
        vec3 rotate3 = vec3(rotate.x, rotate.y, rotate.z);
        this->look_at = rotate3 + this->position;
    }
}

void Camera3D::control(std::string control_name, int value, float dt)
{

}