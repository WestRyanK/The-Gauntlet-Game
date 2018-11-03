#include "CodeMonkeys/Engine/Engine/Renderer.h"
#include "CodeMonkeys/Engine/Objects/AmbientLight.h"
#include "CodeMonkeys/Engine/Objects/DirectionalLight.h"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
#include "glitter.hpp"

using CodeMonkeys::Engine::Engine::Renderer;

Renderer::Renderer(GLFWwindow* window, GLuint width, GLuint height)
{
    this->window = window;
    this->width = width;
    this->height = height;
}

void Renderer::clear()
{
    glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::set_lighting(ShaderProgram* shader, set<ILight3D*> lights)
{
    vector<AmbientLight*> ambients;
    vector<DirectionalLight*> directionals;
    for (ILight3D* light : lights)
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

void Renderer::set_camera(ShaderProgram* shader, Camera3D* camera)
{
    camera->update_shader_with_camera(shader);
}

void Renderer::draw_objects(Object3D* world_root, ShaderProgram* shader)
{
    this->draw_objects_iterator.draw(world_root, shader);
}
        
void Renderer::render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox)
{
    this->clear();

    if (skybox != NULL)
        skybox->draw(camera->get_view_transform(), camera->get_perpective_projection());
    for (ShaderProgram* shader : shaders)
    {
        shader->use_program();

        this->set_lighting(shader, lights); // TODO: investigate 1282 error
        this->set_camera(shader, camera); // TODO: investigate 1282 error

        this->draw_objects(world_root, shader);
    }

    glfwSwapBuffers(this->window);
}


GLuint Renderer::get_width()
{
    return this->width;
}

GLuint Renderer::get_height()
{
    return this->height;
}

// void Renderer::set_width(GLuint width)
// {
//     this->width = width;
// }

// void Renderer::set_height(GLuint height)
// {
//     this->height = height;
// }

GLFWwindow* Renderer::get_window()
{
    return this->window;
}