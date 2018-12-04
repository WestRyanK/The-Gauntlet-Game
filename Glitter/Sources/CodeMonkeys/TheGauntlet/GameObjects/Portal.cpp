#include "CodeMonkeys/TheGauntlet/GameObjects/Portal.h"
#include <string>
#include <Portal.h>
#include "NIE.h"

using CodeMonkeys::TheGauntlet::GameObjects::Portal;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

Portal::Portal(Model3D* model) : PhysicalObject3D(model, "portal")
{
    this->bounding_sphere = new BoundingSphere(this->position, 1000);
    this->set_scale(3.0f);
}

ICollisionRegion* Portal::get_collision_region()
{
    return this->bounding_sphere;
}

void Portal::update(float dt)
{
    PhysicalObject3D::update(dt);
    this->bounding_sphere->set_center(this->position);
}