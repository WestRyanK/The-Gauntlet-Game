#include "UpdateObjectsIterator.h"

using CodeMonkeys::Engine::Engine::UpdateObjectsIterator;

void UpdateObjectsIterator::visit_object(Object3D* object)
{
    if (object != NULL)
    {
        object->update(this->dt);
        this->collision_detector->update(object);

        if (this->boundary_checker != NULL)
            this->boundary_checker->check_boundary(object);
    }
}

void UpdateObjectsIterator::post_visit_children(Object3D* parent)
{
}

void UpdateObjectsIterator::update(Object3D* world_root, float dt)
{
    this->dt = dt;
    this->traverse(world_root);
}

void UpdateObjectsIterator::set_collision_detector(ICollisionDetector* collision_detector)
{
    this->collision_detector = collision_detector;
}

void UpdateObjectsIterator::set_boundary_checker(BoundaryChecker *checker)
{
    this->boundary_checker = checker;
}