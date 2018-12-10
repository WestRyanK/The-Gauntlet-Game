#include "CodeMonkeys/TheGauntlet/Weapons/GravityProjectile.h"

using CodeMonkeys::TheGauntlet::Weapons::GravityProjectile;

GravityProjectile::GravityProjectile(Model3D* model, Billboard* billboard, string name, float total_lifespan, ParticleEmitter* emitter, unsigned int inflict_amount) 
    : Projectile(model, billboard, name, total_lifespan, emitter, inflict_amount)
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
    Model3D* model_clone = NULL;
    Billboard* billboard_clone = NULL;
    if (this->model != NULL)
        model_clone = this->model->clone();
    if (this->billboard != NULL)
        billboard_clone = this->billboard->clone();

    GravityProjectile* projectile_clone = new GravityProjectile(model_clone, billboard_clone, this->name, this->total_lifespan, this->emitter, this->get_inflict_amount());
    projectile_clone->set_angular_velocity(this->get_angular_velocity());
    projectile_clone->set_velocity(this->get_velocity());
    projectile_clone->set_position(this->get_position());
    projectile_clone->set_rotation(this->get_rotation());
    projectile_clone->set_scale(this->get_scale());
    projectile_clone->set_collision_region(this->collision_region);
    return projectile_clone;
}