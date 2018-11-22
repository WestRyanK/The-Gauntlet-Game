#pragma once

#include "WorldObjectsIterator.h"
#include "CodeMonkeys/Engine/Collision/ICollisionDetector.h"

namespace CodeMonkeys::Engine::Engine
{
    class UpdateObjectsIterator : public WorldObjectsIterator
    {
    private:
        float dt;
        virtual void visit_object(Object3D* object);
        virtual void post_visit_children(Object3D* parent);
        ICollisionDetector* collision_detector;
    public:
        void set_collision_detector(ICollisionDetector* collision_detector);
        void update(Object3D* world_root, float dt);
    };
}