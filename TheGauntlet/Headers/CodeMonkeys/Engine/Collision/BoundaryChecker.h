#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::Engine::Collision
{
    class BoundaryChecker
    {
    private:
        vec3 positive_bounds;
        vec3 negative_bounds;

    public:
        BoundaryChecker(vec3 positive_bounds, vec3 negative_bounds);
        void check_boundary(PhysicalObject3D* obj);
        void check_boundary(Object3D* obj);
    };

}