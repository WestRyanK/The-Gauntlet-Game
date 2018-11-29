#pragma once

#include "CodeMonkeys/Engine/Objects/Billboard.h";
#include "CodeMonkeys/Engine/Objects/Particle.h";
#include "CodeMonkeys/Engine/Assets/Texture.h";
namespace CodeMonkeys::Engine::Objects { class ParticleEmitter; }

using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::Engine::Objects
{
    class BillboardParticle : public Particle
    {
    protected:
        Billboard* billboard;
    public:
        BillboardParticle(Billboard* billboard, string name, float total_lifespan, ParticleEmitter* emitter);
        virtual Particle* clone();
        void update(float dt);
        virtual void draw(mat4 total_transform, ShaderProgram* shader);
    };
}