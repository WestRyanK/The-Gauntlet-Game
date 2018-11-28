#pragma once

#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Portal : public PhysicalObject3D
    {
    public:
        Portal(Model3D* model);
    };
}