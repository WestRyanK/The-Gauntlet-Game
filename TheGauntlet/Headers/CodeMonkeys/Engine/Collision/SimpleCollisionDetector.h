#pragma once

#include <set>
#include <map>
#include "CodeMonkeys/Engine/Collision/ICollisionDetector.h"

using namespace std;

namespace CodeMonkeys::Engine::Collision
{
    class SimpleCollisionDetector : public ICollisionDetector
    {
    private:
        set<Object3D*>* objects;
        // vector<Object3D*>* objects;
        void create_objects();
    public:
        SimpleCollisionDetector();
        void clear();
        void insert(Object3D* object);
        void remove(Object3D* object);
        void update(Object3D* object);
        set<pair<Object3D*, Object3D*>> get_collisions();
    };
}