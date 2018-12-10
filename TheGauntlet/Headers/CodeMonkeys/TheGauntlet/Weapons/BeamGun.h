#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/AlternatingWeapon.h"

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class BeamGun : public AlternatingWeapon
    {
    public:
        BeamGun(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}