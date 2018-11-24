#pragma once

#include <set>
#include "Controller.h"
#include "CodeMonkeys/Engine/Control/Controller.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"
#include "CodeMonkeys/Engine/Objects/ILight3D.h"
#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"
#include "CodeMonkeys/Engine/Collision/ICollisionDetector.h"
#include "CodeMonkeys/Engine/Engine/Stopwatch.h"
#include "CodeMonkeys/Engine/Engine/UpdateObjectsIterator.h"
#include "CodeMonkeys/Engine/Engine/Renderer.h"
#include "CodeMonkeys/Engine/Objects/Skybox.h"

using namespace CodeMonkeys::Engine::Control;
using namespace CodeMonkeys::Engine::Collision;

namespace CodeMonkeys::Engine::Engine
{
    class GameEngine
    {
    private:
        GLFWwindow* window;
        Stopwatch stopwatch;
        ICollisionDetector* collision_detector = NULL;
        UpdateObjectsIterator update_objects_iterator;
        GLuint width;
        GLuint height;

    protected:
        set<Controller*> controllers;
        Object3D* world_root;
        set<ILight3D*> lights;
        set<ShaderProgram*> shaders;
        set<ICollisionResponse*> collision_responses;
        Camera3D* camera;
        Skybox* skybox;
        Renderer* renderer;

        bool is_running = false;

        GLFWwindow* get_window();
        GLuint get_width();
        GLuint get_height();
        void set_width(GLuint width);
        void set_height(GLuint height);
        virtual void set_collision_detector(ICollisionDetector* collision_detector);

        virtual void handle_controllers(float dt);
        virtual void update_objects(float dt);
        virtual void handle_collisions(float dt);
        virtual void update_frame(float dt) = 0;
        void draw();
    
    public:
        GameEngine(GLFWwindow* window, GLuint width, GLuint height);
        void run();
        virtual void init() = 0;


        Object3D* get_world_root();
    };

}
