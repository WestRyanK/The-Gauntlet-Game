#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/TheGauntlet/IDamageable.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Asteroid : public PhysicalObject3D, public IDamageable
    {
    private:
        unsigned int size_class;
        float size;
        BoundingSphere* bounding_sphere;
        void on_death();

    public:
        Asteroid(Model3D* model, unsigned int size_class, unsigned int health, float size);
        unsigned int get_size_class();
        float get_size();
        unsigned int get_health();
        virtual void update(float dt);
        ICollisionRegion* get_collision_region();
        static const unsigned int LARGE = 3;
        static const unsigned int MEDIUM = 2;
        static const unsigned int SMALL = 1;

        static const unsigned int LARGE_HEALTH = 30;
        static const unsigned int MEDIUM_HEALTH = 20;
        static const unsigned int SMALL_HEALTH = 10;
    };
}