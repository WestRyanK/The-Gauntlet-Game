#pragma once

#include "CodeMonkeys/TheGauntlet/Weapon.h"

namespace CodeMonkeys::TheGauntlet
{
    class LaserTurret : public Weapon
    {
    protected:
        virtual void on_fire();
    public:
        LaserTurret(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}