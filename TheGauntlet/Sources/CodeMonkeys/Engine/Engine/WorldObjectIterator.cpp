#include "CodeMonkeys/Engine/Engine/WorldObjectsIterator.h"

using CodeMonkeys::Engine::Engine::WorldObjectsIterator;

void WorldObjectsIterator::traverse(Object3D* object)
{
    this->visit_object(object);
    for (Object3D* child : object->get_children())
    {
        this->traverse(child);
    }
    this->post_visit_children(object->get_parent());
}