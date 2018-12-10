#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/AlternatingWeapon.h"

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class LaserTurret : public AlternatingWeapon
    {
    public:
        LaserTurret(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}