#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"

using CodeMonkeys::Engine::Objects::Particle;
using namespace CodeMonkeys::Engine::Objects;

Particle::Particle(Model3D* model, string name, float total_lifespan, ParticleEmitter* emitter) : PhysicalObject3D(model, name)
{
    this->total_lifespan = total_lifespan;
    this->current_lifespan = 0;
    this->emitter = emitter;
}

Particle* Particle::clone()
{
    Particle* particle_clone = new Particle(this->model, this->name, this->total_lifespan, this->emitter);
    particle_clone->set_angular_velocity(this->get_angular_velocity());
    particle_clone->set_velocity(this->get_velocity());
    particle_clone->set_position(this->get_position());
    particle_clone->set_rotation(this->get_rotation());
    particle_clone->set_scale(this->get_scale());
    particle_clone->set_collision_region(this->collision_region);
    return particle_clone;
}

void Particle::update(float dt)
{
    PhysicalObject3D::update(dt);
    if (this->collision_region != NULL)
    {
        this->collision_region->set_center(this->get_position());
    }

    this->current_lifespan += dt;
    if (this->current_lifespan > this->total_lifespan)
    {
        this->emitter->kill_particle(this);
    }
}

ParticleEmitter* Particle::get_emitter()
{
    return this->emitter;
}

void Particle::draw(mat4 total_transform, ShaderProgram* shader)
{
    PhysicalObject3D::draw(total_transform, shader);
}

void Particle::set_collision_region(BoundingMultiSphere* collision_region)
{
    this->collision_region = collision_region;
}

ICollisionRegion* Particle::get_collision_region()
{
    return this->collision_region;
}