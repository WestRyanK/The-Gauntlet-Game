#pragma once

namespace CodeMonkeys::TheGauntlet
{
    class IFlyable 
    {
    protected:
        float xy_acceleration = 1;
        float boost_acceleration = 1;
        float brake_acceleration = 0.5;
        float max_xy_velocity = 1;
        float max_z_velocity = 10;
        float min_z_velocity = 1;
        float max_roll = 25;
        float roll_acceleration = 10;
        float deroll_percent = 0.95;
    
    public:
        IFlyable( float xy_acceleration, 
            float boost_acceleration,
            float brake_acceleration,
            float max_xy_velocity,
            float max_z_velocity,
            float min_z_velocity);
    };
}