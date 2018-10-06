#include "DrawObjectsIterator.h"

using CodeMonkeys::Engine::Engine::DrawObjectsIterator;

void DrawObjectsIterator::visit_object(Object3D* object)
{
    mat4 transform = object->get_transform();
    if (!this->transform_stack.empty())
    {
        mat4 parent_transform = this->transform_stack.top();
        transform = transform * parent_transform;
    }
    this->transform_stack.push(transform);

    object->draw(transform);
}

void DrawObjectsIterator::post_visit_children(Object3D* parent)
{
    if (!this->transform_stack.empty())
    {
        this->transform_stack.pop();
    }
}

void DrawObjectsIterator::draw(Object3D* world_root)
{
    this->traverse(world_root);
}