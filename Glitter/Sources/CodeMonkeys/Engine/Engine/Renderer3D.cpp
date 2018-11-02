#include "CodeMonkeys/Engine/Engine/Renderer3D.h"

using CodeMonkeys::Engine::Engine::Renderer3D;

Renderer3D::Renderer3D(GLFWwindow* window, int width, int height, float camera_spacing) : FrameBufferRenderer(window, width, height)
{
    this->camera_spacing = camera_spacing;
}

Camera3D* Renderer3D::create_second_camera(Camera3D* camera)
{
    Camera3D* second_camera = new Camera3D();
    vec3 sideways = normalize(cross(camera->get_up(), camera->get_look_at() - camera->get_position()));
    vec3 offset = sideways * this->camera_spacing;

    second_camera->set_position(camera->get_position() + offset);
    second_camera->set_look_at(camera->get_look_at());

    return second_camera;
}

void Renderer3D::render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox)
{
    Camera3D* second_camera = create_second_camera(camera);
    vector<Camera3D*> cameras = vector<Camera3D*>();
    cameras.push_back(camera);
    cameras.push_back(second_camera);

    GLuint half_width = this->get_width() / 2;

    for(int i = 0; i < cameras.size(); i++)
    {
        this->set_frame_buffer(this->frame_buffer, half_width * i, 0, half_width, this->get_height());

        this->clear();
        this->set_lighting(shaders, lights); // TODO: investigate 1282 error
        this->set_camera(shaders, cameras[i]); // TODO: investigate 1282 error
        // "action!"
        if (skybox != NULL)
            skybox->draw(cameras[i]->get_view_transform(), cameras[i]->get_perpective_projection());

        this->draw_objects(world_root);
    }

    this->draw_frame_buffer(this->rendered_texture);
    glfwSwapBuffers(this->get_window());

    free(second_camera);
}