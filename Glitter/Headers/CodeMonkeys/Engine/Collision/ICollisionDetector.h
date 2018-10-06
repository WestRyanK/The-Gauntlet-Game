#pragma once

#include <utility>
#include <set>
#include "CodeMonkeys/Engine/Collision/ICollisionRegion.h"
#include "CodeMonkeys/Engine/Collision/BoundingBox.h"
#include "CodeMonkeys/Engine/Objects/Object3D.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::Engine::Collision
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
