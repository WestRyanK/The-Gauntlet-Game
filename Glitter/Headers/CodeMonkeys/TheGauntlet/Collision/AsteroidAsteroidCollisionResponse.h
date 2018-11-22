#pragma once

#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"

namespace CodeMonkeys::TheGauntlet::Collision
{
    class AsteroidAsteroidCollisionResponse : public ICollisionResponse
    {
    public:
        virtual bool can_respond(Object3D* object_a, Object3D* object_b);
        virtual void respond(Object3D* object_a, Object3D* object_b, float dt);
    };
}