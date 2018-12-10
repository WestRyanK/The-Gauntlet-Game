#pragma once

#include "CodeMonkeys/Engine/Collision/BoundingBox.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"

namespace CodeMonkeys::Engine::Collision
{
    class IntersectDetector
    {
    public:
        static bool is_intersection(ICollisionRegion* region_a, ICollisionRegion* region_b);
        // static bool is_intersection(BoundingBox* region_a, BoundingBox* region_b);
        static bool is_intersection(BoundingSphere* region_a, BoundingSphere* region_b);
        // static bool is_intersection(BoundingBox* region_a, BoundingSphere* region_b);
        // static bool is_intersection(BoundingSphere* region_a, BoundingBox* region_b);
    };
}