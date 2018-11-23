#pragma once

#include <utility>
#include <set>
#include "CodeMonkeys/Engine/Collision/ICollisionRegion.h"
#include "CodeMonkeys/Engine/Collision/BoundingBox.h"
#include "CodeMonkeys/Engine/Objects/Object3D.h"

using namespace CodeMonkeys::Engine::Objects;
using namespace std;

namespace CodeMonkeys::Engine::Collision
{
    class ICollisionDetector
    {
    private:
        vec3 positive_bounds;
        vec3 negative_bounds;
        bool is_duplicate(set<pair<Object3D*, Object3D*>>* collisions, Object3D* object_a, Object3D* object_b);
    protected:
        vec3 get_transformed_position(Object3D* object);
        void get_collisions_among_objects(set<pair<Object3D*, Object3D*>>* collisions, set<Object3D*>* objects_a, set<Object3D*>* objects_b);
    public:
        ICollisionDetector(vec3 positive_bounds, vec3 negative_bounds);
        virtual void clear() = 0;
        virtual void insert(Object3D* object) = 0;
        virtual void remove(Object3D* object) = 0;
        virtual void update(Object3D* object) = 0;
        virtual set<pair<Object3D*, Object3D*>> get_collisions() = 0;

        vec3 get_negative_bounds();
        vec3 get_positive_bounds();
    };
}
