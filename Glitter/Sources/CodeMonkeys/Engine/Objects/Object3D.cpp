#include "CodeMonkeys/Engine/Objects/Object3D.h"
#include "NIE.h"

using CodeMonkeys::Engine::Objects::Object3D;

Object3D::Object3D(Model3D* model)
{
    this->model = model;
    this->position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    this->rotation = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    this->scale = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    
    // throw NotImplementedException("Object3D::constructor");
}

vec4 Object3D::get_position()
{
    return this->position;
}

void Object3D::set_position(vec4 position)
{
    this->position = position;
}

vec4 Object3D::get_rotation()
{
    return this->rotation;
}

void Object3D::set_rotation(vec4 rotation)
{
    this->rotation = rotation;
}

vec4 Object3D::get_scale()
{
    return this->scale;
}

void Object3D::set_scale(vec4 scale)
{
    this->scale = scale;
}

void Object3D::set_scale(float scale)
{
    this->scale = vec4(scale, scale, scale, 1.0);
}

// Gets the transform matrix combining Object3D's position, rotation, and scale.
mat4 Object3D::get_transform()
{
    mat4 transform;
    // transform = transform * position * rotation * scale;
    return transform;
    // throw NotImplementedException("Object3D::get_transform");
}

set<Object3D*> Object3D::get_children()
{
    return this->children;
}

void Object3D::add_child(Object3D* child)
{
    if (!this->children.count(child))
        this->children.insert(child);
}

void Object3D::remove_child(Object3D* child)
{
    if (this->children.count(child))
        this->children.erase(child);
}

Object3D* Object3D::get_parent()
{
    return this->parent;
}

void Object3D::set_parent(Object3D* parent)
{
    this->parent = parent;
}

void Object3D::update(float dt)
{
    // throw NotImplementedException("Object3D::update");
}

void Object3D::draw(mat4 total_transform)
{
    if (this->model != NULL)
    {
        this->model->draw();
    }
    // throw NotImplementedException("Object3D::draw");
}