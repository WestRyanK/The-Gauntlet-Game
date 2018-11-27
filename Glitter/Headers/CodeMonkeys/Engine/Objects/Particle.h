#pragma once

#include "CodeMonkeys/Engine/Objects/Billboard.h";
#include "CodeMonkeys/Engine/Assets/Texture.h";
namespace CodeMonkeys::Engine::Objects { class ParticleEmitter; }

using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::Engine::Objects
{
    class Particle: public Billboard
    {
    private:
        float total_lifespan;
        float current_lifespan;
    public:
        Particle(string name, Texture* texture, float width, float height, float total_lifespan);
        Particle(const Particle& particle);
        void update(float dt);
    };
}