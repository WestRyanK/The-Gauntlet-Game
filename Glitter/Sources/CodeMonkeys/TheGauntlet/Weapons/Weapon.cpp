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

    vec4 rotation_vector = vec4(0, 0, 1, 0);
    mat4 transform = this->get_hierarchical_transform();
    vec4 forward_vector = rotation_vector * transform;
    Particle* projectile_clone = this->projectile_prototype->clone();
    projectile_clone->set_position(this->get_transformed_position());
    projectile_clone->set_rotation(this->get_parent()->get_rotation());
    projectile_clone->set_velocity( this->initial_velocity * vec3(forward_vector.x, forward_vector.y, -forward_vector.z));
    this->projectile_emitter->emit(projectile_clone);
}