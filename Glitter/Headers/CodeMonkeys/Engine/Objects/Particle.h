#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"

namespace CodeMonkeys::Engine::Objects { class ParticleEmitter; }

namespace CodeMonkeys::Engine::Objects
{
    class Particle : public PhysicalObject3D
    {
    protected:
        float total_lifespan;
        float current_lifespan;
        ParticleEmitter* emitter;
        ICollisionRegion* collision_region;
    public:
        Particle(Model3D* model, string name, float total_lifespan, ParticleEmitter* emitter);
        virtual Particle* clone();
        void update(float dt);
        ParticleEmitter* get_emitter();
        virtual void draw(mat4 total_transform, ShaderProgram* shader);
        void set_collision_region(ICollisionRegion* collision_region);
    };
}