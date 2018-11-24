#pragma once

#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"

using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::Collision
{
    class ShipAsteroidCollisionResponse : public ICollisionResponse
    {
    private:
        AnimatedTexture* explosion_animation;
    public:
        ShipAsteroidCollisionResponse();//CodeMonkeys::Engine::Engine::GameEngine* engine);
        virtual bool can_respond(Object3D* object_a, Object3D* object_b);
        virtual void respond(Object3D* object_a, Object3D* object_b, float dt);
    };
}