#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/Weapon.h"

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class LaserTurret : public Weapon
    {
    protected:
        virtual void on_fire();
    public:
        LaserTurret(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}