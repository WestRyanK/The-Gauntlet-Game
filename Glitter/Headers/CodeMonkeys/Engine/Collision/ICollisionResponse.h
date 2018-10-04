#pragma once

#include "Object3D.h"

namespace CodeMonkeys::TheGauntlet::Engine::Collision
{
    class ICollisionResponse
    {
    public:
        virtual bool can_respond(Object3D* object_a, Object3D* object_b) = 0;
        virtual void respond(Object3D* object_a, Object3D* object_b) = 0;
    };
}
