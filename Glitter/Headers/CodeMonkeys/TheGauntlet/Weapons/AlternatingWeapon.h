#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/Weapon.h"

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class AlternatingWeapon : public Weapon
    {
    protected:
        virtual void on_fire();
    public:
        AlternatingWeapon(string name, ShaderProgram* shader, ParticleEmitter* projectile_emitter, float initial_velocity, float recharge_delay, bool is_automatic_fire);
    };
}