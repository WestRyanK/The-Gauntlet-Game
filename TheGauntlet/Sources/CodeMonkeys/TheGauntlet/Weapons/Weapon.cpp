#include "CodeMonkeys/TheGauntlet/Weapons/Weapon.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"

using CodeMonkeys::TheGauntlet::Weapons::Weapon;
using namespace CodeMonkeys::Engine::Objects;


Weapon::Weapon(string name, ShaderProgram* shader, ParticleEmitter* projectile_emitter, float initial_velocity, float recharge_delay, bool is_automatic_fire) : PhysicalObject3D(NULL, name), ITriggerable(recharge_delay, is_automatic_fire)
{
    this->projectile_emitter = projectile_emitter;
    this->initial_velocity = initial_velocity;
    this->shader = shader;

    this->sound = new sf::Sound();
    this->sound->setVolume(80.0f);
}

void Weapon::on_fire()
{ 
    if (this->sound_buffer != NULL)
    {
        this->sound->play();
    }

    Particle* projectile_clone = this->projectile_prototype->clone();
    projectile_clone->set_position(this->get_transformed_position());
    projectile_clone->set_velocity( this->initial_velocity * vec3(this->fire_direction.x, this->fire_direction.y, this->fire_direction.z));

    auto transformation = glm::transpose(glm::lookAt(vec3(0), this->fire_direction, glm::vec3(0, 1, 0)));
    auto rotation = glm::quat(transformation);
    projectile_clone->set_rotation(vec3(glm::degrees(rotation.x), glm::degrees(rotation.y), glm::degrees(rotation.z)));
    

    this->projectile_emitter->emit(projectile_clone);
}

void Weapon::set_fire_direction(vec3 fire_direction)
{
    this->fire_direction = fire_direction;
}