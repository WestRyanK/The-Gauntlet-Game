#pragma once

#include "glitter.hpp"
#include "CodeMonkeys/Engine/Objects/Object3D.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::Engine::Engine
{
    class WorldObjectsIterator
    {
    private:

    protected:
        void traverse(Object3D* object);
        virtual void visit_object(Object3D* object) = 0;
        virtual void post_visit_children(Object3D* parent) = 0;
    };
}