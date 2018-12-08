#include "CodeMonkeys/Engine/Collision/BoundaryChecker.h"

using namespace CodeMonkeys::Engine::Collision;

BoundaryChecker::BoundaryChecker(vec3 positive_bounds, vec3 negative_bounds)
{
    this->positive_bounds = positive_bounds;
    this->negative_bounds = negative_bounds;
}

void BoundaryChecker::check_boundary(Object3D* obj)
{
    if (obj == nullptr) return;
    // TODO: Dynamic casts are extremely expensive at runtime, consider doing object type enums instead
     auto phys_obj = dynamic_cast<PhysicalObject3D*> (obj);
     if (phys_obj != NULL)
         check_boundary(phys_obj);
}

void BoundaryChecker::check_boundary(PhysicalObject3D* obj)
{
    // std::set<string> valid_objects = {"ship"};
    std::set<string> valid_objects = {"asteroid", "ship"};
    if (valid_objects.count(obj->get_name()) == 0)
        return;

    vec3 position = obj->get_transformed_position();
    vec3 velocity = obj->get_velocity();

    for (int i = 0; i < 3; i++)
    {
        if (position[i] > positive_bounds[i])
        {
            position[i] = positive_bounds[i];
            if (velocity[i] > 0 && obj->get_name() == "asteroid")
                velocity[i] = -velocity[i];

        }
        if (position[i] < negative_bounds[i])
        {
            position[i] = negative_bounds[i];
            if (velocity[i] < 0 && obj->get_name() == "asteroid")
                velocity[i] = -velocity[i];

        }
    }
    // if (position.x >= max_x && velocity.x > 0 || position.x <= min_x && velocity.x < 0)
    //     velocity.x = -velocity.x;

    // if (position.y >= max_y && velocity.y > 0 || position.y <= min_y && velocity.y < 0)
    //     velocity.y = -velocity.y;

    // if (position.z >= max_z && velocity.z > 0 || position.z <= min_z && velocity.z < 0)
    //     velocity.z = -velocity.z;

    obj->set_position(position);
    obj->set_velocity(velocity);
}

