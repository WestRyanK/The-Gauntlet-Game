#include "CodeMonkeys/TheGauntlet/IFlyable.h"

using CodeMonkeys::TheGauntlet::IFlyable;

IFlyable::IFlyable(
            float xy_acceleration, 
            float boost_acceleration,
            float brake_acceleration,
            float max_xy_velocity,
            float max_z_velocity,
            float min_z_velocity)
{
    this->xy_acceleration = xy_acceleration;
    this->boost_acceleration = boost_acceleration;
    this->brake_acceleration = brake_acceleration;
    this->max_xy_velocity = max_xy_velocity;
    this->max_z_velocity = max_z_velocity;
    this->min_z_velocity = min_z_velocity;
}