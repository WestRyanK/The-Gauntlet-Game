#pragma once

#include "PhysicalObject3D.h"

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Asteroid : public PhysicalObject3:D
    {
    private:
        unsigned int size;
        unsigned int random_seed;

    public:
        unsigned int get_size();
        unsigned int get_health();
    }
}