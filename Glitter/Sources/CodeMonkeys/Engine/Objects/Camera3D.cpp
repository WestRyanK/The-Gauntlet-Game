#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "glitter.hpp"
#include "NIE.h"

using namespace glm;
using CodeMonkeys::Engine::Objects::Camera3D;

Camera3D::Camera3D() : Object3D(NULL, "Camera")
{
    this->look_at = vec3(0.0f, -5.0f, 0.0f);
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

void Camera3D::update_shader_with_camera(ShaderProgram shader)
{
    mat4 view = glm::lookAt(this->position, this->look_at, this->up);

    unsigned int view_location = glGetUniformLocation(shader, "view_transform");
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

    unsigned int projection_location = glGetUniformLocation(shader, "projection_transform");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(this->perspective_projection));
}

void Camera3D::control(std::string control_name, float value, float dt)
{
    const float velocity = 10.0f;
    if (control_name == "move_x")
    {
        this->position.x += value * dt * velocity;
        this->look_at.x += value * dt * velocity;
    }
    if (control_name == "move_y")
    {
        this->position.y += value * dt * velocity;
        this->look_at.y += value * dt * velocity;
    }
    if (control_name == "move_z")
    {
        this->position.z += value * dt * velocity;
        this->look_at.z += value * dt * velocity;
    }
}

void Camera3D::control(std::string control_name, int value, float dt)
{

}