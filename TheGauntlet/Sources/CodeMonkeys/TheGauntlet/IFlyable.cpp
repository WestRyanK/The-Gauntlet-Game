#include "CodeMonkeys/TheGauntlet/IFlyable.h"
#include <stdlib.h>
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"

using namespace CodeMonkeys::Engine::Objects;

using CodeMonkeys::TheGauntlet::IFlyable;

IFlyable::IFlyable(float xy_acceleration, 
            float xy_dampen,
            float max_xy_velocity,
            float z_acceleration,
            float z_dampen,
            float max_z_velocity,
            float min_z_velocity,
            PhysicalObject3D* iflyable)
{
    this->xy_acceleration = xy_acceleration;
    this->xy_dampen = xy_dampen;
    this->max_xy_velocity = max_xy_velocity;
    this->z_acceleration = z_acceleration;
    this->z_dampen = z_dampen;
    this->max_z_velocity = max_z_velocity;
    this->min_z_velocity = min_z_velocity;

    this->iflyable = iflyable;

    this->accelerating_x = false;
    this->accelerating_y = false;
    this->accelerating_z = false;
}


void IFlyable::update_movement(float dt)
{
    this->update_x_movement(dt);
    this->update_y_movement(dt);
    this->update_z_movement(dt);

    this->accelerating_x = false;
    this->accelerating_y = false;
    this->accelerating_z = false;
}

void IFlyable::update_x_movement(float dt)
{
    if (!this->accelerating_x)
        this->dampen_x(dt);

    if (iflyable->get_velocity().x > max_xy_velocity)
        iflyable->set_velocity(0, max_xy_velocity);

    if (iflyable->get_velocity().x < -max_xy_velocity)
        iflyable->set_velocity(0, -max_xy_velocity);

     iflyable->set_rotation(2, -iflyable->get_velocity().x / max_xy_velocity * 40.0f);
}

void IFlyable::dampen_x(float dt)
{
    float dampen_factor = this->xy_dampen * dt;
    if (iflyable->get_velocity().x > 0.0f)
        iflyable->set_velocity(0, std::max(iflyable->get_velocity().x - dampen_factor, 0.0f));

    if (iflyable->get_velocity().x < 0.0f)
        iflyable->set_velocity(0, std::min(iflyable->get_velocity().x + dampen_factor, 0.0f));
}

void IFlyable::update_y_movement(float dt)
{
    if (!this->accelerating_y)
        this->dampen_y(dt);
    
    if (iflyable->get_velocity().y > max_xy_velocity)
        iflyable->set_velocity(1, max_xy_velocity);

    if (iflyable->get_velocity().y < -max_xy_velocity)
        iflyable->set_velocity(1, -max_xy_velocity);

    iflyable->set_rotation(0, iflyable->get_velocity().y / max_xy_velocity * 20.0f);
}

void IFlyable::dampen_y(float dt)
{
    float dampen_factor = 100 * dt;
    if (iflyable->get_velocity().y > 0.0f)
        iflyable->set_velocity(1, std::max(iflyable->get_velocity().y - dampen_factor, 0.0f));

    if (iflyable->get_velocity().y < 0.0f)
        iflyable->set_velocity(1, std::min(iflyable->get_velocity().y + dampen_factor, 0.0f));
}

void IFlyable::update_z_movement(float dt)
{
    if (!this->accelerating_z)
        this->dampen_z(dt);

    if (abs(iflyable->get_velocity().z) < min_z_velocity)
        iflyable->set_velocity(2, -min_z_velocity);
    if (abs(iflyable->get_velocity().z) > max_z_velocity)
        iflyable->set_velocity(2, -max_z_velocity);
}

void IFlyable::dampen_z(float dt)
{
    iflyable->set_velocity(2, iflyable->get_velocity().z + dt * this->z_dampen);
    if (iflyable->get_velocity().z > 0)
    {
        vec3 velocity = iflyable->get_velocity();
        velocity.z = 0;
        iflyable->set_velocity(velocity);
    }
}