#pragma once

#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class ShipFactory
    {
    public:
        static Ship* create_x_wing_ship();
    };
}