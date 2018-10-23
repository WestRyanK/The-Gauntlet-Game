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

void Ship::update(float dt)
{

    printf("%f\n", this->rotation.z);
    printf("%f\n", this->angular_velocity.z);

    PhysicalObject3D::update(dt);
}

void Ship::control(std::string control_name, float value, float dt)
{
    if (control_name == "move_y")
    {
        this->set_velocity(vec3(this->velocity.x, this->velocity.y + value * this->xy_acceleration * dt, this->velocity.z));
        // this->velocity.y += value * this->xy_acceleration * dt;

        // This math isn't technically correct, if you move in both x&y at 
        // same time at max_xy_velocity in each axis, you will actually be travelling max_xy_velocity * sqrt(2)
        if (this->velocity.y > this->max_xy_velocity)
        {
            this->set_velocity(vec3(this->velocity.x, this->max_xy_velocity, this->velocity.z));
        }
        if (this->velocity.y < -this->max_xy_velocity)
        {
            this->set_velocity(vec3(this->velocity.x, -this->max_xy_velocity, this->velocity.z));
        }
    }
    if (control_name == "move_x")
    {
        this->set_velocity(vec3(this->velocity.x + value * this->xy_acceleration * dt, this->velocity.y, this->velocity.z));
        // this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z - value * this->roll_acceleration * dt));

        // This math isn't technically correct, if you move in both x&y at 
        // same time at max_xy_velocity in each axis, you will actually be travelling max_xy_velocity * sqrt(2)
        // if (this->velocity.x > this->max_xy_velocity)
        // {
        //     this->set_velocity(vec3(this->max_xy_velocity, this->velocity.y, this->velocity.z));
        //     // this->velocity.x = this->max_xy_velocity;
        // }
        // if (this->velocity.x < -this->max_xy_velocity)
        // {
        //     this->set_velocity(vec3(-this->max_xy_velocity, this->velocity.y, this->velocity.z));
        // }


        // if (this->rotation.z >= glm::radians(this->max_roll) && this->angular_velocity.z > 0)
        // {
        //     this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y,0.0f));
        //     // this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z - this->roll_acceleration * 0.2f));
        //     // this->set_rotation(vec3(this->rotation.x, this->rotation.y, this->max_roll));
        // }
        // else if (this->rotation.z <= glm::radians(-this->max_roll) && this->angular_velocity.z < 0)
        // {
        //     this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y,0.0f));
        //     // this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z + this->roll_acceleration * 0.2f));
        //     // this->set_rotation(vec3(this->rotation.x, this->rotation.y, -this->max_roll));
        // }
        // if (value == 0)
        // {

        //     // this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z * 0.5f));
        //     this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y,0.0f));
        //     this->set_rotation(vec3(this->rotation.x, this->rotation.y, this->rotation.z * this->deroll_percent));
        //     printf("No x\n");
        // }
        // else
        // {
        //     printf("x\n");
        // }

    }
    if (control_name == "boost")
    {
        this->set_velocity(vec3(this->velocity.x, this->velocity.y, this->velocity.z - value * this->boost_acceleration * dt));
        // this->velocity.z -= value * this->boost_acceleration * dt;

        if (this->velocity.z < -this->max_z_velocity)
        {
            this->set_velocity(vec3(this->velocity.x, this->velocity.y, -this->max_z_velocity));
            // this->velocity.z = this->max_z_velocity;
        }
    }
    if (control_name == "brake")
    {
        this->set_velocity(vec3(this->velocity.x, this->velocity.y, this->velocity.z + value * this->boost_acceleration * dt));
        // this->velocity.z += value * this->brake_acceleration * dt;

        if (this->velocity.z > -this->min_z_velocity)
        {
            // this->velocity.z = this->min_z_velocity;
            this->set_velocity(vec3(this->velocity.x, this->velocity.y, -this->min_z_velocity));
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