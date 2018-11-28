#include "CodeMonkeys/TheGauntlet/Projectile.h"

using CodeMonkeys::TheGauntlet::Projectile;

Projectile::Projectile(Model3D* model, string name, float total_lifespan, ParticleEmitter* emitter, unsigned int inflict_amount) 
    : Particle(model, name, total_lifespan, emitter), 
    IInflicter(inflict_amount)
{

}

Particle* Projectile::clone()
{
    Projectile* projectile_clone = new Projectile(this->model, this->name, this->total_lifespan, this->emitter, this->get_inflict_amount());
    projectile_clone->set_angular_velocity(this->get_angular_velocity());
    projectile_clone->set_velocity(this->get_velocity());
    projectile_clone->set_position(this->get_position());
    projectile_clone->set_rotation(this->get_rotation());
    projectile_clone->set_scale(this->get_scale());
    projectile_clone->set_collision_region(this->collision_region);
    return projectile_clone;
}

void Projectile::update(float dt)
{
    Particle::update(dt);
}