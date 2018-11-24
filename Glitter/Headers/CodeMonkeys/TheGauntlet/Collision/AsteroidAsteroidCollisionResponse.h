#pragma once

#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"

namespace CodeMonkeys::TheGauntlet::Collision
{
    class AsteroidAsteroidCollisionResponse : public ICollisionResponse
    {
    public:
        AsteroidAsteroidCollisionResponse();//CodeMonkeys::Engine::Engine::GameEngine* engine);
        virtual bool can_respond(Object3D* object_a, Object3D* object_b);
        virtual void respond(Object3D* object_a, Object3D* object_b, float dt);
    };
}