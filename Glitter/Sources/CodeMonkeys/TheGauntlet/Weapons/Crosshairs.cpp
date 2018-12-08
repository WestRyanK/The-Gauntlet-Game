#include "CodeMonkeys/TheGauntlet/Weapons/Crosshairs.h"

using CodeMonkeys::TheGauntlet::Weapons::Crosshairs;

Crosshairs::Crosshairs(Texture* texture) : Billboard("crosshairs", texture, 15, 15)
{
    this->position = vec3(0,0, -distance);
    this->update_crosshairs();
}

void Crosshairs::set_crosshairs_x(float aim_x)
{
    this->position.x = aim_x;
    this->update_crosshairs();
}

void Crosshairs::set_crosshairs_y(float aim_y)
{
    this->position.y = aim_y;
    this->update_crosshairs();
}

void Crosshairs::move_crosshairs_x(float delta_x)
{
    this->position.x += delta_x * speed;
    this->update_crosshairs();
}

void Crosshairs::move_crosshairs_y(float delta_y)
{
    this->position.y += delta_y * speed;
    this->update_crosshairs();
}

vec3 Crosshairs::get_aim_vector()
{
    vec3 crosshairs_position = this->get_transformed_position();
    vec3 camera_position = this->camera->get_transformed_position();
    vec3 parent_position = this->parent->get_transformed_position();
    return normalize(crosshairs_position - parent_position);
}

void Crosshairs::update_crosshairs()
{
    if (this->position.x < -this->boundary.x)
        this->position.x = -this->boundary.x;
    if (this->position.y < -this->boundary.y)
        this->position.y = -this->boundary.y;
    if (this->position.x > this->boundary.x)
        this->position.x = this->boundary.x;
    if (this->position.y > this->boundary.y)
        this->position.y = this->boundary.y;

    this->position.z = -this->distance;

    this->set_position(this->position);
}

void Crosshairs::set_speed(float speed)
{
    this->speed = speed;
}

void Crosshairs::set_distance(float distance)
{
    this->distance = distance;
}

void Crosshairs::set_boundary(vec2 boundary)
{
    this->boundary = boundary;
}

float Crosshairs::get_speed()
{
    return this->speed;
}

float Crosshairs::get_distance()
{
    return this->distance;
}

vec2 Crosshairs::get_boundary()
{
    return this->boundary;
}

void Crosshairs::set_camera(Camera3D* camera)
{
    this->camera = camera;
}