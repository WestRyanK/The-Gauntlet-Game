#pragma once

#include <SFML/Audio.hpp>
#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/TheGauntlet/IScoreKeeper.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"

using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::Collision
{
    class ShipAsteroidCollisionResponse : public ICollisionResponse
    {
    private:
        sf::SoundBuffer* sound_buffer = NULL;
        IScoreKeeper* score_keeper;
        sf::Sound* sound = NULL;

    public:
        ShipAsteroidCollisionResponse( CodeMonkeys::Engine::Engine::GameEngine* engine, IScoreKeeper* score_keeper);
        virtual bool can_respond(Object3D* object_a, Object3D* object_b);
        virtual void respond(Object3D* object_a, Object3D* object_b, float dt);
    };
}