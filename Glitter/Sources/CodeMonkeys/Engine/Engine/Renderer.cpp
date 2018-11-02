#include "CodeMonkeys/Engine/Engine/Renderer.h"
#include "CodeMonkeys/Engine/Objects/AmbientLight.h"
#include "CodeMonkeys/Engine/Objects/DirectionalLight.h"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
#include "glitter.hpp"

using CodeMonkeys::Engine::Engine::Renderer;

Renderer::Renderer(GLFWwindow* window)
{
    this->window = window;
}

void Renderer::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::set_lighting(set<ShaderProgram*> shaders, set<ILight3D*> lights)
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

    for (ShaderProgram* shader : shaders)
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

void Renderer::set_camera(set<ShaderProgram*> shaders, Camera3D* camera)
{
    for (ShaderProgram* shader : shaders)
    {
        camera->update_shader_with_camera(shader);
    }
}

void Renderer::draw_objects(Object3D* world_root)
{
    this->draw_objects_iterator.draw(world_root);
}
        
void Renderer::render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox)
{
    this->clear();
    this->set_lighting(shaders, lights); // TODO: investigate 1282 error
    this->set_camera(shaders, camera); // TODO: investigate 1282 error
    // "action!"
    if (skybox != NULL)
        skybox->draw(camera->get_view_transform(), camera->get_perpective_projection());

    this->draw_objects(world_root);

    glfwSwapBuffers(this->window);
}