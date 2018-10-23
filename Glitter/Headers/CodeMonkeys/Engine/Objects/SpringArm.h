#pragma once 

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"

using namespace glm;

namespace CodeMonkeys::Engine::Objects
{
    class SpringArm : public PhysicalObject3D
    {
    private:
        vec3 arm_connector_position;
        // vec3 arm_connector_rotation;
        float spring_constant;
        float arm_connector_mass;
        float arm_length;

    public:
        SpringArm(float arm_length, float spring_constant, float arm_connector_mass);
        mat4 get_transform();
        void update(float dt);
    };
}