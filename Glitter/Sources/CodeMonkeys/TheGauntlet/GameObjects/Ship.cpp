#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IDamageable.h"
#include "CodeMonkeys/Engine/Events/EventDispatcher.h"
#include <string>
#include "CodeMonkeys/TheGauntlet/IFlyable.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"
#include "NIE.h"
#include <algorithm>

using CodeMonkeys::TheGauntlet::GameObjects::Ship;
using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::TheGauntlet::Weapons;

Ship::Ship(Model3D* model, std::string name,
    unsigned int initial_health,
    unsigned int max_health, 

    float xy_acceleration,
    float xy_dampen,
    float max_xy_velocity,
    float z_acceleration,
    float z_dampen,
    float max_z_velocity,
    float min_z_velocity,

    Weapon* primary_weapon,
    Weapon* secondary_weapon,
    RocketEngine* rocket_engine,
    Crosshairs* crosshairs) : 

        PhysicalObject3D(model, name), 
        IDamageable(initial_health, max_health), 
        IControllable(), 
        IFlyable( xy_acceleration,
            xy_dampen,
            max_xy_velocity,
            z_acceleration,
            z_dampen,
            max_z_velocity,
            min_z_velocity,
            this)
{
    this->primary_weapon = primary_weapon;
    this->secondary_weapon = secondary_weapon;
    this->rocket_engine = rocket_engine;
    this->crosshairs = crosshairs;
    if (this->rocket_engine != NULL)
        this->rocket_engine->play();
    this->dead = false;

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
    hide_ship();
    CodeMonkeys::Engine::Events::EventDispatcher::get_instance().report_event("player_died");
}

void Ship::hide_ship()
{
    if (this->rocket_engine != NULL)
        this->rocket_engine->stop();
    this->dead = true;
    this->remove_child(this->rocket_engine);
    this->remove_child(this->crosshairs);
}

void Ship::draw(mat4 total_transform, ShaderProgram* shader)
{
    if (!dead)
        Object3D::draw(total_transform, shader);
}

void Ship::update(float dt)
{
    if (dead)
        return;

    if (this->rocket_engine != NULL)
    {
        this->rocket_engine->update(dt);
        this->rocket_engine->set_is_accelerating(false);
    }

    IFlyable::update_movement(dt);
    PhysicalObject3D::update(dt);
    

    this->bounding_multisphere->set_center(this->position);
    this->bounding_multisphere->set_rotation(this->rotation);

    if (this->primary_weapon != NULL)
        this->primary_weapon->set_fire_direction(glm::normalize(this->crosshairs->get_aim_vector()));
    if (this->secondary_weapon != NULL)
        this->secondary_weapon->set_fire_direction(glm::normalize(this->crosshairs->get_aim_vector()));
}


void Ship::control(std::string control_name, float value, float dt)
{
    if (this->dead)
        return;

    if ((control_name == "move_x" || control_name == "move_z" || control_name == "move_y") && value != 0)
    {
        if (this->rocket_engine != NULL)
            this->rocket_engine->set_is_accelerating(true);
    }

    if (control_name == "move_x")
    {
        if (value != 0.0f)
            this->accelerating_x = true;
        this->velocity.x += value * dt * this->xy_acceleration;
    }
    if (control_name == "move_y")
    {
        if (value != 0.0f)
            this->accelerating_y = true;
        this->velocity.y += value * dt * this->xy_acceleration;
    }

    if (control_name == "move_z" && value == 1)
    {
        this->accelerating_z = true;
        this->velocity.z -= dt * this->z_acceleration;
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
    if (this->dead)
        return;

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
bool Ship::is_dead()
{
    return this->dead;
}