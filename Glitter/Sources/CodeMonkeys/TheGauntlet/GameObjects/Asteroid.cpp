#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include <string>
#include "NIE.h"

using CodeMonkeys::TheGauntlet::GameObjects::Asteroid;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

Asteroid::Asteroid(Model3D* model, unsigned int size_class, unsigned int health, float size) : PhysicalObject3D(model, "asteroid"), IDamageable(health, health)
{
    this->size_class = size_class;
    this->size = size;
    // TODO: Adjust size
    this->bounding_sphere = new BoundingSphere(this->position, size);
}

void Asteroid::on_death()
{
    throw NotImplementedException("Asteroid::on_death");
}

void Asteroid::update(float dt)
{
    PhysicalObject3D::update(dt);
    this->bounding_sphere->set_center(this->position);
}

ICollisionRegion* Asteroid::get_collision_region()
{
    return this->bounding_sphere;
}

unsigned int Asteroid::get_size_class()
{
    return this->size_class;
}

float Asteroid::get_size()
{
    return this->size;
}