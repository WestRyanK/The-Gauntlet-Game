#include "CodeMonkeys/Engine/Objects/Object3D.h"
#include <string>
#include "NIE.h"

using CodeMonkeys::Engine::Objects::Object3D;

Object3D::Object3D(Model3D* model, std::string name)
{
    this->model = model;
    this->position = vec3(0.0f, 0.0f, 0.0f);
    this->rotation = vec3(0.0f, 0.0f, 0.0f);
    this->scale = vec3(1.0f, 1.0f, 1.0f);

    this->name = name;
}

vec3 Object3D::get_position()
{
    return this->position;
}

void Object3D::set_position(vec3 position)
{
    this->position = position;
}

vec3 Object3D::get_rotation()
{
    return this->rotation;
}

void Object3D::set_rotation(vec3 rotation)
{
    this->rotation = rotation;
}

vec3 Object3D::get_scale()
{
    return this->scale;
}

void Object3D::set_scale(vec3 scale)
{
    this->scale = scale;
}

void Object3D::set_scale(float scale)
{
    this->scale = vec3(scale, scale, scale);
}

vec3 Object3D::get_transformed_position()
{
    vec4 position = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    mat4 transform = this->get_hierarchical_transform();
    position = transform * position;

    return vec3(position.x, position.y, position.z);
}

mat4 Object3D::get_hierarchical_transform()
{
    mat4 transform;
    Object3D* parent_object = this;
    while (parent_object != NULL)
    {
        transform = parent_object->get_transform() * transform;
        parent_object = parent_object->get_parent();
    }

    return transform;
}

// Gets the transform matrix combining Object3D's position, rotation, and scale.
mat4 Object3D::get_transform()
{
    mat4 transform;
    transform = glm::translate(transform, this->position);
    transform = glm::rotate(transform, glm::radians(this->rotation.y), vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(this->rotation.z), vec3(0, 0, 1));
    transform = glm::rotate(transform, glm::radians(this->rotation.x), vec3(1, 0, 0));
    transform = glm::scale(transform, this->scale);
    // transform = position * rotation * scale * transform;
    return transform;
}

set<Object3D*> Object3D::get_children()
{
    return this->children;
}

void Object3D::add_child(Object3D* child)
{
    if (child->parent != NULL)
        child->parent->remove_child(child);

    if (!this->children.count(child))
        this->children.insert(child);

        child->parent = this;
}

void Object3D::remove_child(Object3D* child)
{
    if (this->children.count(child))
        this->children.erase(child);
    child->parent = NULL;
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
}

void Object3D::draw(mat4 total_transform, ShaderProgram* shader)
{
    if (this->model != NULL)
    {
        this->model->draw(total_transform, shader);
    }
}

ICollisionRegion* Object3D::get_collision_region()
{
    return NULL;
}

std::string Object3D::get_name()
{
    return this->name;
}