#pragma once

#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"

namespace CodeMonkeys::TheGauntlet::Collision
{
    class ShipPortalCollisionResponse : public ICollisionResponse
    {
    public:
        ShipPortalCollisionResponse(
                // );
                CodeMonkeys::Engine::Engine::GameEngine* engine);
        virtual bool can_respond(Object3D* object_a, Object3D* object_b);
        virtual void respond(Object3D* object_a, Object3D* object_b, float dt);
    };
}