#pragma once

#include "WorldObjectsIterator.h"

namespace CodeMonkeys::Engine::Engine
{
    class UpdateObjectsIterator : public WorldObjectsIterator
    {
    private:
        float dt;
        virtual void visit_object(Object3D* object);
        virtual void post_visit_children(Object3D* parent);
    public:
        void update(Object3D* world_root, float dt);
    };
}