#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Collision/ICollisionRegion.h"

using namespace glm;

namespace CodeMonkeys::Engine::Collision
{
    class BoundingSphere : public ICollisionRegion
    {
    private:
        vec3 center;
        float radius;
    public:
        BoundingSphere(vec3 center, float radius);
        vec3 get_center();
        void set_center(vec3 center);
        float get_radius();
        void set_radius(float radius);
    };
}