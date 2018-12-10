#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"
#include <set>

using namespace glm;
using namespace std;

namespace CodeMonkeys::Engine::Collision
{
    class BoundingMultiSphere : public ICollisionRegion
    {
    private:
        vec3 center;
        vec3 rotation;
        set<BoundingSphere*> spheres;
    public:
        BoundingMultiSphere(vec3 center, vec3 rotation);
        vec3 get_center();
        void set_center(vec3 center);
        vec3 get_rotation();
        void set_rotation(vec3 rotation);
        void add_sphere(BoundingSphere* sphere);
        set<BoundingSphere*> get_spheres();
        void free_spheres(set<BoundingSphere*> spheres);
    };
}