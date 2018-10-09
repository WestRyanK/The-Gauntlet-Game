#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/Object3D.h"
#include "CodeMonkeys/Engine/Assets/Model3D.h"

using namespace glm;
using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::Engine::Objects
{
    class PhysicalObject3D: public Object3D
    {
    protected:
        vec3 velocity;
        vec3 angular_velocity;

    public:
        PhysicalObject3D(Model3D* model);

        vec3 get_velocity();
        void set_velocity(vec3 velocity);
        vec3 get_angular_velocity();
        void set_angular_velocity(vec3 angular_velocity);
        virtual void update(float dt);
    };
}
