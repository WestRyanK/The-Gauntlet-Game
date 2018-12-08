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

const float max_lateral_velocity = 200.0f;
const float min_forward_velocity = 100;
const float max_forward_velocity = 200;
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
    Weapon* secondary_weapon,
    RocketEngine* rocket_engine,
    Crosshairs* crosshairs) : 

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
    this->rocket_engine = rocket_engine;
    this->crosshairs = crosshairs;
    if (this->rocket_engine != NULL)
        this->rocket_engine->play();
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
    if (this->rocket_engine != NULL)
        this->rocket_engine->stop();
    throw NotImplementedException("Ship::on_death");
}

void Ship::update(float dt)
{
    if (this->rocket_engine != NULL)
    {
        this->rocket_engine->update(dt);
        this->rocket_engine->set_is_accelerating(false);
    }

    this->update_vertical(dt);
    this->update_lateral(dt);
    this->update_forward(dt);

    PhysicalObject3D::update(dt);
    
    this->acclerating_vertically = false;
    this->acclerating_laterally = false;
    this->accelerating_forward = false;

    this->bounding_multisphere->set_center(this->position);
    this->bounding_multisphere->set_rotation(this->rotation);

    if (this->primary_weapon != NULL)
        this->primary_weapon->set_fire_direction(glm::normalize(this->crosshairs->get_aim_vector()));
    if (this->secondary_weapon != NULL)
        this->secondary_weapon->set_fire_direction(glm::normalize(this->crosshairs->get_aim_vector()));
}

void Ship::update_forward(float dt)
{
    float dampen_factor = 10;
    if (!this->accelerating_forward)
    {
        this->velocity.z += dt * dampen_factor;
    }
    if (abs(this->velocity.z) < min_forward_velocity)
        this->velocity.z = -min_forward_velocity;
    if (abs(this->velocity.z) > max_forward_velocity)
        this->velocity.z = -max_forward_velocity;
}

void Ship::update_lateral(float dt)
{
    if (!this->acclerating_laterally)
        this->dampen_lateral(dt);

    if (this->velocity.x > max_lateral_velocity)
        this->velocity.x = max_lateral_velocity;

    if (this->velocity.x < -max_lateral_velocity)
        this->velocity.x = -max_lateral_velocity;

     this->rotation.z = -this->velocity.x / max_lateral_velocity * 40.0f;
}

void Ship::update_vertical(float dt)
{
    if (!this->acclerating_vertically)
        this->dampen_vertical(dt);
    
    if (this->velocity.y > max_lateral_velocity)
        this->velocity.y = max_lateral_velocity;

    if (this->velocity.y < -max_lateral_velocity)
        this->velocity.y = -max_lateral_velocity;

    this->rotation.x = this->velocity.y / max_lateral_velocity * 20.0f;
}

void Ship::dampen_lateral(float dt)
{
    float dampen_factor = 100 * dt;
    if (this->velocity.x > 0.0f)
        this->velocity.x = std::max(this->velocity.x - dampen_factor, 0.0f);

    if (this->velocity.x < 0.0f)
        this->velocity.x = std::min(this->velocity.x + dampen_factor, 0.0f);
}

void Ship::dampen_vertical(float dt)
{
    float dampen_factor = 100 * dt;
    if (this->velocity.y > 0.0f)
        this->velocity.y = std::max(this->velocity.y - dampen_factor, 0.0f);

    if (this->velocity.y < 0.0f)
        this->velocity.y = std::min(this->velocity.y + dampen_factor, 0.0f);
}

void Ship::control(std::string control_name, float value, float dt)
{
    if ((control_name == "move_x" || control_name == "move_z" || control_name == "move_y") && value != 0)
    {
        if (this->rocket_engine != NULL)
            this->rocket_engine->set_is_accelerating(true);
    }
    const float velocity = 100.0f;
    vec3 forward = vec3(0, 0, 1);

    if (control_name == "move_x")
    {
        if (value != 0.0f)
            this->acclerating_laterally = true;
        this->velocity.x += value * dt * 200;
    }
    if (control_name == "move_y")
    {
        if (value != 0.0f)
            this->acclerating_vertically = true;
        this->velocity.y += value * dt * 200;
    }

    if (control_name == "move_z" && value == 1)
    {
        this->accelerating_forward = true;
        this->velocity.z += dt * -400;
        // this->position += forward * dt * value * velocity * 2.0f;
    }

    if (control_name == "aim_x")
    {
        this->crosshairs->move_crosshairs_x(value * dt);
    }

    if (control_name == "aim_y")
    {
        this->crosshairs->move_crosshairs_y(-value * dt);
    }
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

Weapon* Ship::get_primary_weapon()
{
    return this->primary_weapon;
}

Weapon* Ship::get_secondary_weapon()
{
    return this->secondary_weapon;
}

Crosshairs* Ship::get_crosshairs()
{
    return this->crosshairs;
}