#include "CodeMonkeys/Engine/Engine/GameEngine.h"
#include "glitter.hpp"
#include <typeinfo>
#include "CodeMonkeys/Engine/Control/Controller.h"
#include "CodeMonkeys/Engine/Objects/Object3D.h"
#include "CodeMonkeys/Engine/Objects/Camera3D.h"
#include "CodeMonkeys/Engine/Objects/AmbientLight.h"
#include "CodeMonkeys/Engine/Objects/DirectionalLight.h"
#include "NIE.h"

using CodeMonkeys::Engine::Engine::GameEngine;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Control;

GameEngine::GameEngine(GLFWwindow* window)
{
    this->window = window;
    this->world_root = new Object3D(NULL, "world_root");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE or GL_FILL
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  
    // throw NotImplementedException("GameEngine::constructor");
}

void GameEngine::set_lighting()
{
    vector<AmbientLight*> ambients;
    vector<DirectionalLight*> directionals;
    for (ILight3D* light : this->lights)
    {
        if (dynamic_cast<AmbientLight*>(light) != NULL)
        {
            ambients.push_back(dynamic_cast<AmbientLight*>(light));
        }
        if (dynamic_cast<DirectionalLight*>(light) != NULL)
        {
            directionals.push_back(dynamic_cast<DirectionalLight*>(light));
        }
    }

    for (ShaderProgram* shader : this->shaders)
    {
        ILight3D::set_light_count(shader, "ambient", ambients.size());
        ILight3D::set_light_count(shader, "directional", directionals.size());
        for (int i = 0; i < ambients.size(); i++)
        {
            ambients[i]->add_light_to_shader(shader, i);
        }
        for (int i = 0; i < directionals.size(); i++)
        {
            directionals[i]->add_light_to_shader(shader, i);
        }
    }
}


void GameEngine::set_camera()
{
    for (ShaderProgram* shader : this->shaders)
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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
        dt = this->stopwatch.get_seconds_from_last_measurement();
        if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            this->is_running = false;

        this->update_frame(dt);
        glfwPollEvents();
    }
}

