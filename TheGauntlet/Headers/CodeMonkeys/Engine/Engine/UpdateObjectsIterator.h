#pragma once

#include "WorldObjectsIterator.h"
#include "CodeMonkeys/Engine/Collision/ICollisionDetector.h"
#include "CodeMonkeys/Engine/Collision/BoundaryChecker.h"

namespace CodeMonkeys::Engine::Engine
{
    class UpdateObjectsIterator : public WorldObjectsIterator
    {
    private:
        float dt;
        virtual void visit_object(Object3D* object);
        virtual void post_visit_children(Object3D* parent);
        ICollisionDetector* collision_detector;
        BoundaryChecker* boundary_checker;
    public:
        void set_collision_detector(ICollisionDetector* collision_detector);
        void set_boundary_checker(BoundaryChecker* checker);
        void update(Object3D* world_root, float dt);
    };
}