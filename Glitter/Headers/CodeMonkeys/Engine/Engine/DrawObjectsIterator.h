#pragma once

#include "WorldObjectsIterator.h"
#include <stack>
#include "CodeMonkeys/Engine/Objects/Object3D.h"

using namespace CodeMonkeys::Engine;


namespace CodeMonkeys::Engine::Engine
{
    class DrawObjectsIterator : public WorldObjectsIterator
    {
    private:
        std::stack<mat4> transform_stack;
        virtual void visit_object(Objects::Object3D* object);
        virtual void post_visit_children(Objects::Object3D* parent);
    public:
        void draw(Objects::Object3D* world_root);
    };
}