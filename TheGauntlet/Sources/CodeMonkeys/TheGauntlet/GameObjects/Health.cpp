#include "CodeMonkeys/TheGauntlet/GameObjects/Health.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IInflicter.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"

using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Collision;
using namespace CodeMonkeys::TheGauntlet::Weapons;

using CodeMonkeys::TheGauntlet::GameObjects::Health;

Health::Health(int healing_value) :  Billboard("health", new Texture("Assets/Health/health.png"), 15, 15), IInflicter(healing_value)
{
    this->bounding_sphere = new BoundingSphere(this->position, 10);
}

ICollisionRegion* Health::get_collision_region()
{
    return this->bounding_sphere;
}

void Health::update(float dt)
{
    PhysicalObject3D::update(dt);
    this->bounding_sphere->set_center(this->position);
}