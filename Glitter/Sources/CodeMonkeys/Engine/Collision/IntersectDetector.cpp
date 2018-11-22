#include "CodeMonkeys/Engine/Collision/IntersectDetector.h"
#include "CodeMonkeys/Engine/Collision/BoundingMultiSphere.h"

using CodeMonkeys::Engine::Collision::IntersectDetector;

bool IntersectDetector::is_intersection(ICollisionRegion* region_a, ICollisionRegion* region_b)
{
    BoundingSphere* sphere_a = dynamic_cast<BoundingSphere*> (region_a);
    BoundingSphere* sphere_b = dynamic_cast<BoundingSphere*> (region_b);

    BoundingMultiSphere* multi_sphere_a = dynamic_cast<BoundingMultiSphere*> (region_a);
    BoundingMultiSphere* multi_sphere_b = dynamic_cast<BoundingMultiSphere*> (region_b);

    if (sphere_a != NULL && sphere_b != NULL)
        return is_intersection((BoundingSphere*)sphere_a, (BoundingSphere*)sphere_b);
    else if (multi_sphere_a != NULL && sphere_b != NULL)
    {
        auto spheres = multi_sphere_a->get_spheres();
        bool intersect = false;
        for (auto s : spheres)
        {
            intersect |= is_intersection((BoundingSphere*) s, (BoundingSphere*) sphere_b);
        }
        multi_sphere_a->free_spheres(spheres);
        return intersect;
    }

    
    return false;
}

// bool IntersectDetector::is_intersection(BoundingBox* region_a, BoundingBox* region_b)
// {
// }

bool IntersectDetector::is_intersection(BoundingSphere* region_a, BoundingSphere* region_b)
{
    float intersect_distance = region_a->get_radius() + region_b->get_radius();
    vec3 offset_between = region_a->get_center() - region_b->get_center();

    return (glm::length(offset_between) <= intersect_distance);
}

// bool IntersectDetector::is_intersection(BoundingBox* region_a, BoundingSphere* region_b)
// {
    
// }

// bool IntersectDetector::is_intersection(BoundingSphere* region_a, BoundingBox* region_b)
// {
    
// }