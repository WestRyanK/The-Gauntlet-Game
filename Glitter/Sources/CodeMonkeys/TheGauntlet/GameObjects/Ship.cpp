#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/TheGauntlet/IDamageable.h"
#include <string>
#include "CodeMonkeys/TheGauntlet/IFlyable.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"
#include "NIE.h"

using CodeMonkeys::TheGauntlet::GameObjects::Ship;
using namespace CodeMonkeys::TheGauntlet;

Ship::Ship(Model3D* model, std::string name,
    unsigned int initial_health,
    unsigned int max_health, 

    float xy_acceleration, 
    float boost_acceleration,
    float brake_acceleration,
    float max_xy_velocity,
    float max_z_velocity,
    float min_z_velocity,

    IFireable* primary_weapon,
    IFireable* secondary_weapon) : 

        PhysicalObject3D(model, name), 
        IDamageable(initial_health, max_health), 
        IControllable(), 
        IFlyable(xy_acceleration, 
            boost_acceleration,
            brake_acceleration,
            max_xy_velocity,
            max_z_velocity,
            min_z_velocity)
{
    this->primary_weapon = primary_weapon;
    this->secondary_weapon = secondary_weapon;
}

void Ship::on_death()
{
    throw NotImplementedException("Ship::on_death");
}

void Ship::control(std::string control_name, float value, float dt)
{
    if (control_name == "move_y")
    {
        this->velocity.y += value * this->xy_acceleration * dt;

        // This math isn't technically correct, if you move in both x&y at 
        // same time at max_xy_velocity in each axis, you will actually be travelling max_xy_velocity * sqrt(2)
        if (this->velocity.y > this->max_xy_velocity)
        {
            this->velocity.y = this->max_xy_velocity;
        }
    }
    if (control_name == "move_x")
    {
        this->velocity.x += value * this->xy_acceleration * dt;

        // This math isn't technically correct, if you move in both x&y at 
        // same time at max_xy_velocity in each axis, you will actually be travelling max_xy_velocity * sqrt(2)
        if (this->velocity.x > this->max_xy_velocity)
        {
            this->velocity.x = this->max_xy_velocity;
        }
    }
    if (control_name == "boost")
    {
        this->velocity.z += value * this->boost_acceleration * dt;

        if (this->velocity.z > this->max_z_velocity)
        {
            this->velocity.z = this->max_z_velocity;
        }
    }
    if (control_name == "brake")
    {
        this->velocity.z -= value * this->brake_acceleration * dt;

        if (this->velocity.z < this->min_z_velocity)
        {
            this->velocity.z = this->min_z_velocity;
        }
    }
}

void Ship::control(std::string control_name, int value, float dt)
{
    IFireable* weapon = NULL;
    if (control_name == "fire_primary")
    {
        weapon = this->primary_weapon;
    }
    if (control_name == "fire_secondary")
    {
        weapon = this->secondary_weapon;
    }

    if (weapon != NULL)
    {
        if (value == 1)
        {
            weapon->pull_trigger();
        }
        else if (value == 0)
        {
            weapon->release_trigger();
        }
    }
}