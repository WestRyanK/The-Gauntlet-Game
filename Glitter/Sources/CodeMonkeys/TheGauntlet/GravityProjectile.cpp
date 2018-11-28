#include "CodeMonkeys/TheGauntlet/GravityProjectile.h"

using CodeMonkeys::TheGauntlet::GravityProjectile;

GravityProjectile::GravityProjectile(Model3D* model, string name, float total_lifespan, ParticleEmitter* emitter, unsigned int inflict_amount) 
    : Projectile(model, name, total_lifespan, emitter, inflict_amount)
{
    
}

void GravityProjectile::update(float dt)
{
    vec3 velocity = this->get_velocity();
    velocity.y -= GRAVITY_AMOUNT * dt;
    this->set_velocity(velocity);
    Projectile::update(dt);
}

Particle* GravityProjectile::clone()
{
    Projectile* projectile_clone = new GravityProjectile(this->model, this->name, this->total_lifespan, this->emitter, this->get_inflict_amount());
    projectile_clone->set_angular_velocity(this->get_angular_velocity());
    projectile_clone->set_velocity(this->get_velocity());
    projectile_clone->set_position(this->get_position());
    projectile_clone->set_rotation(this->get_rotation());
    projectile_clone->set_scale(this->get_scale());
    projectile_clone->set_collision_region(this->collision_region);
    return projectile_clone;
}