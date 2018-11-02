#include "CodeMonkeys/Engine/Engine/GameEngine.h"
#include "glitter.hpp"
#include <typeinfo>
#include "CodeMonkeys/Engine/Control/Controller.h"
#include "CodeMonkeys/Engine/Objects/Object3D.h"
#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "CodeMonkeys/Engine/Objects/AmbientLight.h"
#include "CodeMonkeys/Engine/Objects/DirectionalLight.h"
#include "NIE.h"
#include <stdexcept>

using CodeMonkeys::Engine::Engine::GameEngine;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Control;

GameEngine::GameEngine(GLFWwindow* window)
{
    this->window = window;
    this->world_root = new Object3D(NULL, "world_root");
    this->skybox = NULL;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE or GL_FILL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  
}

GLFWwindow* GameEngine::get_window()
{
    return this->window;
}

void GameEngine::handle_controllers(float dt)
{
    for (Controller* controller : this->controllers)
    {
        controller->handle_input(dt);
    }
}

void GameEngine::draw()
{
    if (this->renderer != NULL)
        this->renderer->render(this->shaders, this->lights, this->camera, this->world_root, this->skybox);
    else
        throw "Must specify renderer for engine!";
}
        
void GameEngine::update_objects(float dt)
{
    this->update_objects_iterator.update(this->world_root, dt);
}
        
void GameEngine::handle_collisions(float dt)
{
    if (this->collision_detector != NULL)
    {
        auto collisions = this->collision_detector->get_collisions();
        
        for (pair<Object3D*, Object3D*> collision : collisions)
        {
            for (ICollisionResponse* collision_response : this->collision_responses)
            {
                if (collision_response->can_respond(collision.first, collision.second))
                {
                    collision_response->respond(collision.first, collision.second);
                }
            }
        }
    }
}
        
void GameEngine::run()
{
    if (this->collision_detector == NULL)
    {
        printf("Collision Detector NULL!\n");
    }

    this->is_running = true;
    float dt = this->stopwatch.get_seconds_from_last_measurement();
    while (this->is_running)
    {
        dt = this->stopwatch.get_seconds_from_last_measurement();
        if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            this->is_running = false;

        this->update_frame(dt);
        glfwPollEvents();
    }
}

