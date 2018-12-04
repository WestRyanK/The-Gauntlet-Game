#pragma once

#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IInflicter.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class Projectile : public Particle, public IInflicter
    {
    public:
        Projectile(Model3D* model, Billboard* billboard, string name, float total_lifespan, ParticleEmitter* emitter, unsigned int inflict_amount);
        virtual Particle* clone();
        virtual void update(float dt);
    };
}