#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/Weapon.h"

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class LaserCannon : public Weapon
    {
    public:
        LaserCannon(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}