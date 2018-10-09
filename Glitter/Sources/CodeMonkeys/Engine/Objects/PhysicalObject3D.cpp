#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "NIE.h"

using CodeMonkeys::Engine::Objects::PhysicalObject3D;
using namespace CodeMonkeys::Engine::Objects;

PhysicalObject3D::PhysicalObject3D(Model3D* model) : Object3D(model)
{
    this->velocity = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    this->angular_velocity = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    // throw NotImplementedException("PhysicalObject3D::constructor");
}

vec4 PhysicalObject3D::get_velocity()
{
    return this->velocity;
}

void PhysicalObject3D::set_velocity(vec4 velocity)
{
    this->velocity = velocity;
}
        
vec4 PhysicalObject3D::get_angular_velocity()
{
    return this->angular_velocity;
}
        
void PhysicalObject3D::set_angular_velocity(vec4 angular_velocity)
{
    this->angular_velocity = angular_velocity;
}

void PhysicalObject3D::update(float dt)
{
    this->position.x += dt * this->velocity.x;
    this->position.y += dt * this->velocity.y;
    this->position.z += dt * this->velocity.z;

    this->rotation.x += dt * this->angular_velocity.x;
    this->rotation.y += dt * this->angular_velocity.y;
    this->rotation.z += dt * this->angular_velocity.z;
}