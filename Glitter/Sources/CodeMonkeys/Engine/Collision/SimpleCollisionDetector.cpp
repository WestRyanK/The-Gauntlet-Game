#include "CodeMonkeys/Engine/Collision/SimpleCollisionDetector.h"
#include "CodeMonkeys/Engine/Collision/IntersectDetector.h"

using CodeMonkeys::Engine::Collision::SimpleCollisionDetector;


SimpleCollisionDetector::SimpleCollisionDetector() : ICollisionDetector(vec3(), vec3())
{
    this->create_objects();
}

void SimpleCollisionDetector::clear()
{
    free(this->objects);
    this->create_objects();
}

void SimpleCollisionDetector::create_objects()
{
    // this->objects = new set<Object3D*>();
    this->objects = new vector<Object3D*>();
}

void SimpleCollisionDetector::insert(Object3D* object)
{
    // this->objects->insert(object);
    this->objects->push_back(object);
}

void SimpleCollisionDetector::remove(Object3D* object)
{
    auto iter = std::find(this->objects->begin(), this->objects->end(), object);
    if (iter != this->objects->end())
        this->objects->erase(iter);
}

void SimpleCollisionDetector::update(Object3D* object)
{
    this->remove(object);
    this->insert(object);
}

set<pair<Object3D*, Object3D*>> SimpleCollisionDetector::get_collisions()
{
    set<pair<Object3D*, Object3D*>> collisions;

    for (auto object_a_iter = this->objects->begin(); object_a_iter != this->objects->end(); object_a_iter++)
    {
        for (auto object_b_iter = this->objects->begin(); object_b_iter != this->objects->end(); object_b_iter++)
        {
            if (*object_a_iter != *object_b_iter)
            {
                if(IntersectDetector::is_intersection((*object_a_iter)->get_collision_region(), (*object_b_iter)->get_collision_region()))
                {
                    collisions.insert(pair<Object3D*, Object3D*>(*object_a_iter, *object_b_iter));
                }
            }
        }
    }
    printf("\n");
    return collisions;
}
