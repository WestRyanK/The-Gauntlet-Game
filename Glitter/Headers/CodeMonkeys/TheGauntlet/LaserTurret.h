#pragma once

#include "CodeMonkeys/TheGauntlet/IFireable.h"

namespace CodeMonkeys::TheGauntlet
{
    class LaserTurret : public IFireable
    {
    private:
        void on_fire();

    public:
        LaserTurret();
    };
}