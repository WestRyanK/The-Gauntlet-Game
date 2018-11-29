#pragma once

#include "CodeMonkeys/TheGauntlet/Weapon.h"

namespace CodeMonkeys::TheGauntlet
{
    class LaserTurret : public Weapon
    {
    public:
        LaserTurret(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}