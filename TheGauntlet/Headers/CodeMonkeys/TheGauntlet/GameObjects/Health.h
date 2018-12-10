#pragma once

#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IInflicter.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"

using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::Weapons;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Health : public Billboard, public IInflicter
    {
    private:
        BoundingSphere* bounding_sphere;

    public:
        Health(int healing_value);
        ICollisionRegion* get_collision_region();
        void update(float dt);
    };
}