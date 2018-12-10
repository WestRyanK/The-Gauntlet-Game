#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/Projectile.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class GravityProjectile : public Projectile
    {
    public:
        GravityProjectile(Model3D* model, Billboard* billboard, string name, float total_lifespan, ParticleEmitter* emitter, unsigned int inflict_amount);
        virtual Particle* clone();
        virtual void update(float dt);
        const float GRAVITY_AMOUNT = 20.0f;
    };
}