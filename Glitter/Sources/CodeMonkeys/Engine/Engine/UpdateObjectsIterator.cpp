#include "UpdateObjectsIterator.h"

using CodeMonkeys::Engine::Engine::UpdateObjectsIterator;

void UpdateObjectsIterator::visit_object(Object3D* object)
{
    object->update(this->dt);
}

void UpdateObjectsIterator::post_visit_children(Object3D* parent)
{
}

void UpdateObjectsIterator::update(Object3D* world_root, float dt)
{
    this->dt = dt;
    this->traverse(world_root);
}