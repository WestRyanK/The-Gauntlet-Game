#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/Weapon.h"

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class AntiMatterCannon : public Weapon
    {
    public:
        AntiMatterCannon(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}