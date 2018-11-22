#include "CodeMonkeys/Engine/Collision/ICollisionDetector.h"

using CodeMonkeys::Engine::Collision::ICollisionDetector;

ICollisionDetector::ICollisionDetector(vec3 positive_bounds, vec3 negative_bounds)
{
    this->positive_bounds = positive_bounds;
    this->negative_bounds = negative_bounds;
}

vec3 ICollisionDetector::get_negative_bounds()
{
    return this->negative_bounds;
}

vec3 ICollisionDetector::get_positive_bounds()
{
    return this->positive_bounds;
}