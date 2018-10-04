#pragma once

#include <set>
#include "Controller.h"
#include "Light3D.h"
#include "ICollisionResponse.h"
#include "ICollisionDetector.h"

namespace CodeMonkeys::Engine::Collision
{
    class Engine
    {
    private:
        set<Controller> controllers;
        set<Object3D*> world_objects;
        set<Light3D*> lights;
        set<ShaderProgram> shaders;
        set<ICollisionResponse> collision_responses;
        ICollisionDetector collision_detector;

        void set_lighting();
        void draw_objects();

    protected:
        void handle_controllers();
        void update_objects();
        void handle_collisions();
        void draw();
        virtual void update_frame(float dt) = 0;
    
    public:
        void run();
        virtual void init() = 0;
    }
}