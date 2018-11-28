#pragma once

#include "CodeMonkeys/TheGauntlet/Weapon.h"

namespace CodeMonkeys::TheGauntlet
{
    class LaserCannon : public Weapon
    {
    public:
        LaserCannon(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}