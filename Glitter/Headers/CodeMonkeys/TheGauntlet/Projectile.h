#pragma once

#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/TheGauntlet/IInflicter.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet
{
    class Projectile : public Particle, public IInflicter
    {
    public:
        Projectile(Model3D* model, Billboard* billboard, string name, float total_lifespan, ParticleEmitter* emitter, unsigned int inflict_amount);
        virtual Particle* clone();
        virtual void update(float dt);
    };
}