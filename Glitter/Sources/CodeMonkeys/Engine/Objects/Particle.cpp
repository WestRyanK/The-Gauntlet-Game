#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"


using CodeMonkeys::Engine::Objects::Particle;

Particle::Particle(string name, Texture* texture, float width, float height, float total_lifespan) : Billboard(name, texture, width, height)
{
    this->total_lifespan = total_lifespan;
    this->current_lifespan = 0;
}

Particle::Particle(const Particle& particle) : Particle(particle.name, particle.billboard_texture, particle.width, particle.height, particle.total_lifespan)
{
    this->billboard_texture->reset();
}

void Particle::update(float dt)
{
    Billboard::update(dt);

    this->current_lifespan += dt;
    if (this->current_lifespan > this->total_lifespan)
    {
        ParticleEmitter* emitter = (ParticleEmitter*)this->parent;
        emitter->kill_particle(this);
    }
}