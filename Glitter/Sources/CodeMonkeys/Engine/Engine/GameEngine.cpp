#include "CodeMonkeys/Engine/Engine/GameEngine.h"
#include "CodeMonkeys/Engine/Control/Controller.h"
#include "NIE.h"

using CodeMonkeys::Engine::Engine::GameEngine;
using namespace CodeMonkeys::Engine::Control;

GameEngine::GameEngine(GLFWwindow* window)
{
    this->window = window;
    // throw NotImplementedException("GameEngine::constructor");
}

void GameEngine::set_lighting()
{
    for (ILight3D* light : this->lights)
    {
        for (ShaderProgram shader : this->shaders)
        {
            light->add_light_to_shader(shader);
        }
    }
}

GLFWwindow* GameEngine::get_window()
{
    return this->window;
}

void GameEngine::draw_objects()
{
    this->draw_objects_iterator.draw(this->world_root);
}

void GameEngine::handle_controllers(float dt)
{
    for (Controller* controller : this->controllers)
    {
        controller->handle_input(dt);
    }
}
        
void GameEngine::update_objects(float dt)
{
    this->update_objects_iterator.update(this->world_root, dt);
}
        
void GameEngine::handle_collisions(float dt)
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
        
void GameEngine::draw()
{
    this->set_lighting();
    this->draw_objects();
}
        
void GameEngine::run()
{
    this->is_running = true;
    float dt = this->stopwatch.get_seconds_from_last_measurement();
    while (this->is_running)
    {
        this->update_frame(dt);
    }
}