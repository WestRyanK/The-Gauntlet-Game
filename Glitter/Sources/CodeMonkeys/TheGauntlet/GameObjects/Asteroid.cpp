#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include <string>
#include "NIE.h"

using CodeMonkeys::TheGauntlet::GameObjects::Asteroid;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

Asteroid::Asteroid(Model3D* model, unsigned int size, unsigned int health) : PhysicalObject3D(model, "asteroid"), IDamageable(health, health)
{
    this->size = size;
}

void Asteroid::on_death()
{
    throw NotImplementedException("Asteroid::on_death");
}