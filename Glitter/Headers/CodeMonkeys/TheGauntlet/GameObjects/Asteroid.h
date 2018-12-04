#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/TheGauntlet/IDamageable.h"
#include "CodeMonkeys/TheGauntlet/IInflicter.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Asteroid : public PhysicalObject3D, public IDamageable, public IInflicter
    {
    private:
        unsigned int size_class;
        float size;
        BoundingSphere* bounding_sphere;
        void on_death();
        static ParticleEmitter* asteroid_death_emitter;
        static Billboard* asteroid_death_billboard;

    public:
        Asteroid(Model3D* model, unsigned int size_class, unsigned int health, float size, unsigned int inflict_amount);
        static void init(Object3D* world_root);
        unsigned int get_size_class();
        float get_size();
        unsigned int get_health();
        virtual void update(float dt);
        ICollisionRegion* get_collision_region();
        static const unsigned int LARGE = 3;
        static const unsigned int MEDIUM = 2;
        static const unsigned int SMALL = 1;

        static const unsigned int LARGE_HEALTH = 5;
        static const unsigned int MEDIUM_HEALTH = 3;
        static const unsigned int SMALL_HEALTH = 1;

        static const unsigned int LARGE_INFLICT = 35;
        static const unsigned int MEDIUM_INFLICT = 25;
        static const unsigned int SMALL_INFLICT = 15;
    };
}