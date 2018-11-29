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
#include "CodeMonkeys/Engine/Collision/ICollisionResponse.h"

using CodeMonkeys::Engine::Engine::GameEngine;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Control;

GameEngine::GameEngine(GLFWwindow* window, GLuint width, GLuint height)
{
    this->window = window;
    this->width = width;
    this->height = height;
    this->world_root = new Object3D(NULL, "world_root");
    this->skybox = NULL;
    this->boundary_checker = NULL;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE or GL_FILL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
}


GLuint GameEngine::get_width()
{
    return this->width;
}

GLuint GameEngine::get_height()
{
    return this->height;
}

void GameEngine::set_width(GLuint width)
{
    this->width = width;
}

void GameEngine::set_height(GLuint height)
{
    this->height = height;
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

void GameEngine::set_boundary_checker(BoundaryChecker* checker)
{
    this->boundary_checker = checker;
    this->update_objects_iterator.set_boundary_checker(checker);
}
        
void GameEngine::handle_collisions(float dt)
{
    if (this->collision_detector != NULL)
    {
        auto collisions = this->collision_detector->get_collisions();
        
        for (pair<Object3D*, Object3D*> collision : collisions)
        {
            // printf("Collision between %s and %s!\n", collision.first->get_name().c_str(), collision.second->get_name().c_str());

            for (ICollisionResponse* collision_response : this->collision_responses)
            {
                if (collision_response->can_respond(collision.first, collision.second))
                {
                    collision_response->respond(collision.first, collision.second, dt);
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

void GameEngine::set_collision_detector(ICollisionDetector* collision_detector)
{
    this->collision_detector = collision_detector;
    this->update_objects_iterator.set_collision_detector(collision_detector);
}

Object3D* GameEngine::get_world_root()
{
    return this->world_root;
}