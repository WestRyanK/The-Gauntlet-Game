#pragma once

#include <utility>
#include <set>
#include "ICollisionRegion.h"
#include "BoundingBox.h"

namespace CodeMonkeys::TheGauntlet::Engine::Collision
{
    class ICollisionDetector
    {
    public:
        virtual void clear() = 0;
        virtual void insert(Object3D* object) = 0;
        virtual void remove(Object3D* object) = 0;
        virtual void update(Object3D* object) = 0;
        virtual set<pair<Object3D*, Object3D*>> get_collisions() = 0;
    };
}
