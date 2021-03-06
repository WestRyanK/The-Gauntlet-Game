#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/ITriggerable.h"
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/TheGauntlet/Weapons/Projectile.h"
#include <SFML/Audio.hpp>
#include <string>

using namespace std;
using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class Weapon : public ITriggerable, public PhysicalObject3D
    {
    protected:
        vec3 fire_direction;
        virtual void on_fire();
        Projectile* projectile_prototype = NULL;
        ParticleEmitter* projectile_emitter = NULL;
        float initial_velocity = 0;
        ShaderProgram* shader = NULL;
        sf::SoundBuffer* sound_buffer = NULL;
        sf::Sound* sound = NULL;
    
    public:
        Weapon(string name, ShaderProgram* shader, ParticleEmitter* projectile_emitter, float initial_velocity, float recharge_delay, bool is_automatic_fire);
        void set_fire_direction(vec3 fire_direction);
    };
}