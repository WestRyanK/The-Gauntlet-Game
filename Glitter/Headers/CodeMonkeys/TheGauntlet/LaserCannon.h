#pragma once

#include "CodeMonkeys/TheGauntlet/IFireable.h"

namespace CodeMonkeys::TheGauntlet
{
    class LaserCannon : public IFireable
    {
    private:
        void on_fire();

    public:
        LaserCannon();
    };
}