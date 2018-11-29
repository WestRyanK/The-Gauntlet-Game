#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::Engine::Collision
{
    class BoundaryChecker
    {
    private:
        float max_x, max_y, max_z, min_x, min_y, min_z;

    public:
        BoundaryChecker(float max_x, float max_y, float max_z, float min_x, float min_y, float min_z)
        {
            this->max_x = max_x;
            this->max_y = max_y;
            this->max_z = max_z;
            this->min_x = min_x;
            this->min_y = min_y;
            this->min_z = min_z;
        }
        void check_boundary(PhysicalObject3D* obj);
        void check_boundary(Object3D* obj);
    };

}