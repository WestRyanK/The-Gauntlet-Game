#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet
{
    class IFlyable 
    {
    protected:
        float xy_acceleration;
        float xy_dampen;
        float max_xy_velocity;
        float z_acceleration;
        float z_dampen;
        float max_z_velocity;
        float min_z_velocity;

        bool accelerating_y;
        bool accelerating_x;
        bool accelerating_z;

        PhysicalObject3D* iflyable;

        void update_x_movement(float dt);
        void update_y_movement(float dt);
        void update_z_movement(float dt);
        void dampen_x(float dt);
        void dampen_y(float dt);
        void dampen_z(float dt);
    
    public:
        IFlyable( float xy_acceleration, 
            float xy_dampen,
            float max_xy_velocity,
            float z_acceleration,
            float z_dampen,
            float max_z_velocity,
            float min_z_velocity,
            PhysicalObject3D* iflyable);

        void update_movement(float dt);
    };
}