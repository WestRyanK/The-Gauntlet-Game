#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IDamageable.h"
#include <string>
#include "CodeMonkeys/TheGauntlet/IFlyable.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"
#include "NIE.h"
#include <algorithm>

using CodeMonkeys::TheGauntlet::GameObjects::Ship;
using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::TheGauntlet::Weapons;

const float maxVerticalAngle = 45.0f;
const float maxLateralAccleration = 1.0f;

Ship::Ship(Model3D* model, std::string name,
    unsigned int initial_health,
    unsigned int max_health, 

    float xy_acceleration, 
    float boost_acceleration,
    float brake_acceleration,
    float max_xy_velocity,
    float max_z_velocity,
    float min_z_velocity,

    Weapon* primary_weapon,
    Weapon* secondary_weapon) : 

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
    this->acclerating_vertically = false;
    this->acclerating_laterally = false;

    this->bounding_multisphere = new BoundingMultiSphere(this->position, vec3());
    this->bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, -10.0f), 3.0f));
    this->bounding_multisphere->add_sphere(new BoundingSphere(vec3(0.0f, 0.0f, 5.0f), 3.0f));
    this->bounding_multisphere->add_sphere(new BoundingSphere(vec3(2.0f, 0.0f, 3.0f), 3.0f));
    this->bounding_multisphere->add_sphere(new BoundingSphere(vec3(-2.0f, 0.0f, 3.0f), 3.0f));
    this->bounding_multisphere->add_sphere(new BoundingSphere(vec3(-11.0f, 0.0f, 3.0f), 3.0f));
    this->bounding_multisphere->add_sphere(new BoundingSphere(vec3(11.0f, 0.0f, 3.0f), 3.0f));

    if (this->primary_weapon != NULL)
        this->add_child(this->primary_weapon);
    if (this->secondary_weapon != NULL)
        this->add_child(this->secondary_weapon);
}

void Ship::on_death()
{
    throw NotImplementedException("Ship::on_death");
}

void Ship::update(float dt)
{
    // this->update_vertical(dt);
    // this->update_lateral(dt);
    
    vec4 facing_direction = vec4(0, 0, -1, 0);
    mat4 rotation_matrix;
    // rotation_matrix = glm::rotate(rotation_matrix, this->rotation.z, vec3(1,0,0));
    rotation_matrix = glm::rotate(rotation_matrix, this->rotation.x, vec3(1,0,0));
    rotation_matrix = glm::rotate(rotation_matrix, this->rotation.y, vec3(0,1,0));
    facing_direction = rotation_matrix * facing_direction;

    // float speed = 60;
    // this->set_velocity(vec3(speed * facing_direction));

    // vec3 forward = glm::normalize(this->look_at - this->position);
    // vec3 sideways = -glm::normalize(glm::cross(this->up, this->look_at - this->position));

    PhysicalObject3D::update(dt);
    
    this->acclerating_vertically = false;
    this->acclerating_laterally = false;

    this->bounding_multisphere->set_center(this->position);
    this->bounding_multisphere->set_rotation(this->rotation);
}

void Ship::update_vertical(float dt)
{
    if (!this->acclerating_vertically)
        this->dampen_vertical(dt);
    
    if (this->rotation.x >= glm::radians(maxVerticalAngle))
    {
        this->rotation.x = glm::radians(maxVerticalAngle);
        if (this->angular_velocity.x > 0)
            this->set_angular_velocity(vec3(0, this->angular_velocity.y, this->angular_velocity.z));
        
    }
    if (this->rotation.x <= -glm::radians(maxVerticalAngle))
    {
        this->rotation.x = -glm::radians(maxVerticalAngle);
        if (this->angular_velocity.x < 0)
        {
            
            this->set_angular_velocity(vec3(0, this->angular_velocity.y, this->angular_velocity.z));
        }
    }
}

void Ship::update_lateral(float dt)
{
    if (!this->acclerating_laterally)
        this->dampen_lateral(dt);
    
    if (this->angular_velocity.y > 1)
        this->set_angular_velocity(vec3(this->angular_velocity.x, 1, this->angular_velocity.z));
    
    if (this->angular_velocity.y < -1)
        this->set_angular_velocity(vec3(this->angular_velocity.x, -1, this->angular_velocity.z));
    
    this->rotation.z = this->angular_velocity.y * glm::radians(45.0f);
}

void Ship::dampen_lateral(float dt)
{
    if (this->angular_velocity.y > 0.0f)
        this->angular_velocity.y = std::max(this->angular_velocity.y - dt, 0.0f);
    
    if (this->angular_velocity.y < 0.0f)
        this->angular_velocity.y = std::min(this->angular_velocity.y + dt, 0.0f);
    
    if (this->angular_velocity.z > 0.0f)
        this->angular_velocity.z = std::max(this->angular_velocity.z - dt, 0.0f);
    
    if (this->angular_velocity.z < 0.0f)
        this->angular_velocity.z = std::min(this->angular_velocity.z + dt, 0.0f);
}

void Ship::dampen_vertical(float dt)
{
    if (this->angular_velocity.x > 0.0f)
        this->angular_velocity.x = std::max(this->angular_velocity.x - dt, 0.0f);
    
    if (this->angular_velocity.x < 0.0f)
        this->angular_velocity.x = std::min(this->angular_velocity.x + dt, 0.0f);
}

void Ship::control(std::string control_name, float value, float dt)
{
    // printf("%f %f %f\n", this->position.x, this->position.y, this->position.z);
    const float velocity = 100.0f;
    vec3 forward = vec3(0, 0, 1);
    vec3 sideways = vec3(1, 0, 0);
    if (control_name == "move_x")
    {
        this->position += sideways * dt * value * velocity;
    }
    // if (control_name == "move_y")
    // {
    //     this->position.y += value * dt * velocity;
    // }
    if (control_name == "move_y")
    {
        this->position += forward * dt * value * velocity;
    }
    const float R = 10;
    if (control_name == "boost")
    {
        this->position += vec3(0, 1, 0) * dt * value * velocity * 0.25f;
        // this->rotation = vec3(this->rotation.x, this->rotation.y, this->rotation.z + R);
    }
    if (control_name == "brake")
    {
        this->position -= vec3(0, 1, 0) * dt * value * velocity * 0.25f;
        // this->rotation = vec3(this->rotation.x, this->rotation.y, this->rotation.z - R);
    }

    // if (control_name == "move_y")
    // {
    //     if (value != 0.0f)
    //         this->acclerating_vertically = true;
        
    //     this->set_angular_velocity(vec3(this->angular_velocity.x + value * dt * 2, this->angular_velocity.y, this->angular_velocity.z));
    //     // if (value == 0)
    //     // {
    //     //     if (this->rotation.x < 0 && this->angular_velocity.x < 0  || this->rotation.x > 0 && this->angular_velocity.x > 0)
    //     //     {
    //     //         float x_velocity = this->angular_velocity.x - dt * this->rotation.x * 0.8f;
    //     //         this->set_angular_velocity(vec3(x_velocity, this->angular_velocity.y, this->angular_velocity.z));
    //     //     }
    //     //     if (this->rotation.x < 0 && this->angular_velocity.x >= 0 || this->rotation.x > 0 && this->angular_velocity.x <= 0)
    //     //     {
    //     //         float x_rotation = this->rotation.x * 0.97f;
    //     //         this->set_rotation(vec3(x_rotation, this->rotation.y, this->rotation.z));
    //     //     }
    //     //     // float x_velocity = 0;
    //     //     // if (this->rotation.x != 0)
    //     //     //     x_velocity = this->angular_velocity.x - dt * this->rotation.x * 0.5f;


    //     // }
    //     // this->set_velocity(vec3(this->velocity.x, this->velocity.y + value * this->xy_acceleration * dt, this->velocity.z));
    //     // // this->velocity.y += value * this->xy_acceleration * dt;

    //     // // This math isn't technically correct, if you move in both x&y at 
    //     // // same time at max_xy_velocity in each axis, you will actually be travelling max_xy_velocity * sqrt(2)
    //     // if (this->velocity.y > this->max_xy_velocity)
    //     // {
    //     //     this->set_velocity(vec3(this->velocity.x, this->max_xy_velocity, this->velocity.z));
    //     // }
    //     // if (this->velocity.y < -this->max_xy_velocity)
    //     // {
    //     //     this->set_velocity(vec3(this->velocity.x, -this->max_xy_velocity, this->velocity.z));
    //     // }
    // }
    // if (control_name == "move_x")
    // {
    //     if (value != 0.0f)
    //         this->acclerating_laterally = true;
    //     this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z - value * dt * 2));
    //     this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y- value * dt * 2, this->angular_velocity.z ));
    //     // this->set_velocity(vec3(this->velocity.x + value * this->velocity.z * dt, this->velocity.y, this->velocity.z));

    //     // this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z - value * this->roll_acceleration * dt));

    //     // This math isn't technically correct, if you move in both x&y at 
    //     // same time at max_xy_velocity in each axis, you will actually be travelling max_xy_velocity * sqrt(2)
    //     // if (this->velocity.x > this->max_xy_velocity)
    //     // {
    //     //     this->set_velocity(vec3(this->max_xy_velocity, this->velocity.y, this->velocity.z));
    //     //     // this->velocity.x = this->max_xy_velocity;
    //     // }
    //     // if (this->velocity.x < -this->max_xy_velocity)
    //     // {
    //     //     this->set_velocity(vec3(-this->max_xy_velocity, this->velocity.y, this->velocity.z));
    //     // }


    //     // if (this->rotation.z >= glm::radians(this->max_roll) && this->angular_velocity.z > 0)
    //     // {
    //     //     this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y,0.0f));
    //     //     // this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z - this->roll_acceleration * 0.2f));
    //     //     // this->set_rotation(vec3(this->rotation.x, this->rotation.y, this->max_roll));
    //     // }
    //     // else if (this->rotation.z <= glm::radians(-this->max_roll) && this->angular_velocity.z < 0)
    //     // {
    //     //     this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y,0.0f));
    //     //     // this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z + this->roll_acceleration * 0.2f));
    //     //     // this->set_rotation(vec3(this->rotation.x, this->rotation.y, -this->max_roll));
    //     // }
    //     // if (value == 0)
    //     // {

    //     //     // this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y, this->angular_velocity.z * 0.5f));
    //     //     this->set_angular_velocity(vec3(this->angular_velocity.x, this->angular_velocity.y,0.0f));
    //     //     this->set_rotation(vec3(this->rotation.x, this->rotation.y, this->rotation.z * this->deroll_percent));
    //     //     printf("No x\n");
    //     // }
    //     // else
    //     // {
    //     //     printf("x\n");
    //     // }

    // }
    // if (control_name == "boost")
    // {
    //     // this->set_velocity(vec3(this->velocity.x, this->velocity.y, this->velocity.z - value * this->boost_acceleration * dt));
    //     // // this->velocity.z -= value * this->boost_acceleration * dt;

    //     // if (this->velocity.z < -this->max_z_velocity)
    //     // {
    //     //     this->set_velocity(vec3(this->velocity.x, this->velocity.y, -this->max_z_velocity));
    //     //     // this->velocity.z = this->max_z_velocity;
    //     // }
    // }
    // if (control_name == "brake")
    // {
    //     // this->set_velocity(vec3(this->velocity.x, this->velocity.y, this->velocity.z + value * this->boost_acceleration * dt));
    //     // // this->velocity.z += value * this->brake_acceleration * dt;

    //     // if (this->velocity.z > -this->min_z_velocity)
    //     // {
    //     //     // this->velocity.z = this->min_z_velocity;
    //     //     this->set_velocity(vec3(this->velocity.x, this->velocity.y, -this->min_z_velocity));
    //     // }
    // }
}

void Ship::control(std::string control_name, int value, float dt)
{
    Weapon* weapon = NULL;
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

ICollisionRegion* Ship::get_collision_region()
{
    return this->bounding_multisphere;
}