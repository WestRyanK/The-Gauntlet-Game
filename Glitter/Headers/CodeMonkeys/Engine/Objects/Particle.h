#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"

using namespace CodeMonkeys::Engine::Collision;
namespace CodeMonkeys::Engine::Objects { class ParticleEmitter; }

namespace CodeMonkeys::Engine::Objects
{
    class Particle : public PhysicalObject3D
    {
    protected:
        float total_lifespan;
        float current_lifespan;
        ParticleEmitter* emitter = NULL;
        BoundingSphere* collision_region = NULL;
    public:
        Particle(Model3D* model, string name, float total_lifespan, ParticleEmitter* emitter);
        virtual Particle* clone();
        void update(float dt);
        ParticleEmitter* get_emitter();
        virtual void draw(mat4 total_transform, ShaderProgram* shader);
        void set_collision_region(BoundingSphere* collision_region);
        virtual ICollisionRegion* get_collision_region();
    };
}