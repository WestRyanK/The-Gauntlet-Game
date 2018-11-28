#include "CodeMonkeys/Engine/Objects/BillboardParticle.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"

using CodeMonkeys::Engine::Objects::BillboardParticle;
using namespace CodeMonkeys::Engine::Objects;

BillboardParticle::BillboardParticle(Billboard* billboard, string name, float total_lifespan, ParticleEmitter* emitter) : Particle(NULL, name, total_lifespan, emitter)
{
    this->billboard = billboard;
}

Particle* BillboardParticle::clone()
{
    this->billboard->reset();
    BillboardParticle* particle_copy = new BillboardParticle(this->billboard, this->name, this->total_lifespan, this->emitter);
    return particle_copy;
}

void BillboardParticle::update(float dt)
{
    this->billboard->update(dt);
    Particle::update(dt);
}

void BillboardParticle::draw(mat4 total_transform, ShaderProgram* shader)
{
    this->billboard->draw(total_transform, shader);
}