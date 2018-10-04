#pragma once

#include "Object3D.h"

using namespace glm;

namespace CodeMonkeys::TheGauntlet::Engine::Objects
{
    class PhysicalObject3D: public Object3D
    {
    private:
        vec3 velocity;
        vec3 angular_velocity;

    public:
        PhysicalObject3D();

        vec3 get_velocity();
        void set_velocity(vec3 velocity);
        vec3 get_angular_velocity();
        void set_angular_velocity(vec3 angular_velocity);
    };
}
