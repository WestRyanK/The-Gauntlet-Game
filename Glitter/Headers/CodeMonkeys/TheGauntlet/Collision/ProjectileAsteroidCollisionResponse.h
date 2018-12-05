#pragma once

#include <SFML/Audio.hpp>
#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"

using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::Collision
{
    class ProjectileAsteroidCollisionResponse : public ICollisionResponse
    {
    private:
        ParticleEmitter* projectile_impact_emitter;
        sf::SoundBuffer* sound_buffer = NULL;
        sf::Sound* sound = NULL;
    public:
        ProjectileAsteroidCollisionResponse(
        // );
        CodeMonkeys::Engine::Engine::GameEngine* engine);
        virtual bool can_respond(Object3D* object_a, Object3D* object_b);
        virtual void respond(Object3D* object_a, Object3D* object_b, float dt);
    };
}