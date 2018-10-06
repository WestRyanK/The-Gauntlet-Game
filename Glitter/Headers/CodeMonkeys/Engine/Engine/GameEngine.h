#pragma once

#include <set>
#include "Controller.h"
#include "CodeMonkeys/Engine/Control/Controller.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"
#include "CodeMonkeys/Engine/Objects/ILight3D.h"
#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"
#include "CodeMonkeys/Engine/Collision/ICollisionDetector.h"
#include "CodeMonkeys/Engine/Engine/Stopwatch.h"
#include "CodeMonkeys/Engine/Engine/DrawObjectsIterator.h"
#include "CodeMonkeys/Engine/Engine/UpdateObjectsIterator.h"

using namespace CodeMonkeys::Engine::Control;
using namespace CodeMonkeys::Engine::Collision;

namespace CodeMonkeys::Engine::Engine
{
    class GameEngine
    {
    private:
        set<Controller*> controllers;
        Object3D* world_root;
        set<ILight3D*> lights;
        set<ShaderProgram> shaders;
        set<ICollisionResponse*> collision_responses;
        ICollisionDetector* collision_detector = NULL;
        Stopwatch stopwatch;
        DrawObjectsIterator draw_objects_iterator;
        UpdateObjectsIterator update_objects_iterator;

        void set_lighting();
        void draw_objects();

    protected:
        bool is_running = false;

        virtual void handle_controllers(float dt);
        virtual void update_objects(float dt);
        virtual void handle_collisions(float dt);
        virtual void draw();
        virtual void update_frame(float dt) = 0;
    
    public:
        GameEngine();
        void run();
        virtual void init() = 0;
    };
}