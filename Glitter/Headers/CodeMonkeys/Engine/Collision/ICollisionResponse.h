#pragma once

#include "CodeMonkeys/Engine/Objects/Object3D.h"
using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::Engine::Collision
{
    class ICollisionResponse
    {
    protected:
        // GameEngine* engine;
    public:
        // ICollisionResponse(GameEngine* engine);
        virtual bool can_respond(Object3D* object_a, Object3D* object_b) = 0;
        virtual void respond(Object3D* object_a, Object3D* object_b, float dt) = 0;
    };
}
