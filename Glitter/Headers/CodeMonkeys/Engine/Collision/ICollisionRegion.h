#pragma once

#include "CodeMonkeys/Engine/Collision/BoundingBox.h"

using CodeMonkeys::Engine::Collision::BoundingBox;

namespace CodeMonkeys::TheGauntlet::Engine::Collision
{
    class ICollisionRegion
    {
    private:
        BoundingBox bounding_box;

    public:
    };
}