#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Portal : public PhysicalObject3D
    {
    private:
        BoundingSphere* bounding_sphere;
    public:
        Portal(Model3D* model);
        ICollisionRegion* get_collision_region();
        void update(float dt);
    };
}