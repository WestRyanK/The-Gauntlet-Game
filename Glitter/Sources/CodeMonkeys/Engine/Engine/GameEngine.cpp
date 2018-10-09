#include "CodeMonkeys/Engine/Engine/GameEngine.h"
#include "glitter.hpp"
#include "CodeMonkeys/Engine/Control/Controller.h"
#include "CodeMonkeys/Engine/Objects/Object3D.h"
#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "NIE.h"

using CodeMonkeys::Engine::Engine::GameEngine;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Control;

GameEngine::GameEngine(GLFWwindow* window)
{
    this->window = window;
    this->world_root = new Object3D(NULL);
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

void GameEngine::set_camera()
{
    for (ShaderProgram shader : this->shaders)
    {
        this->camera->update_shader_with_camera(shader);
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
        
void GameEngine::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->set_lighting();
    this->set_camera();
    // "action!"
    this->draw_objects();

    glfwSwapBuffers(this->window);
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
        if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            this->is_running = false;

        this->update_frame(dt);
        glfwPollEvents();
    }
}