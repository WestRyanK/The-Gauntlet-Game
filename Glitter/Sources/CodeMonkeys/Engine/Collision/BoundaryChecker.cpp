#include "CodeMonkeys/Engine/Collision/BoundaryChecker.h"

using namespace CodeMonkeys::Engine::Collision;

void BoundaryChecker::check_boundary(Object3D* obj)
{
    // TODO: Dynamic casts are extremely expensive at runtime, consider doing object type enums instead
    auto phys_obj = dynamic_cast<PhysicalObject3D*> (obj);
    if (phys_obj != NULL)
        check_boundary(phys_obj);
}

void BoundaryChecker::check_boundary(PhysicalObject3D* obj)
{
    vec3 position = obj->get_transformed_position();
    vec3 velocity = obj->get_velocity();

    if (position.x >= max_x && velocity.x > 0 || position.x <= min_x && velocity.x < 0)
        velocity.x = -velocity.x;

    if (position.y >= max_y && velocity.y > 0 || position.y <= min_y && velocity.y < 0)
        velocity.y = -velocity.y;

    if (position.z >= max_z && velocity.z > 0 || position.z <= min_z && velocity.z < 0)
        velocity.z = -velocity.z;

    obj->set_velocity(velocity);
}

