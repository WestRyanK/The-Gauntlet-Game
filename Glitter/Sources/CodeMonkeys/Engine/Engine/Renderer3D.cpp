#include "CodeMonkeys/Engine/Engine/Renderer3D.h"

using CodeMonkeys::Engine::Engine::Renderer3D;

Renderer3D::Renderer3D(GLFWwindow* window, int width, int height, float camera_spacing) : FrameBufferRenderer(window, width, height)
{
    this->camera_spacing = camera_spacing;
    this->create_frame_buffer(this->get_width() / 2, this->get_height(), this->frame_buffers[0], this->rendered_textures[0]);
    this->create_frame_buffer(this->get_width() / 2, this->get_height(), this->frame_buffers[1], this->rendered_textures[1]);
    this->quads[0] = new Quad(-1.0f, -1.0f, 1.0f, 2.0f);
    this->quads[1] = new Quad(0.0f, -1.0f, 1.0f, 2.0f);
}

Camera3D* Renderer3D::create_second_camera(Camera3D* camera)
{
    Camera3D* second_camera = new Camera3D();
    vec3 sideways = normalize(cross(camera->get_up(), camera->get_look_at() - camera->get_position()));
    vec3 offset = sideways * this->camera_spacing;

    second_camera->set_look_at(camera->get_look_at_parent());
    second_camera->set_parent(camera->get_parent());
    second_camera->set_position(camera->get_position());
    second_camera->set_position(camera->get_position() - offset);
    // second_camera->set_look_at(camera->get_look_at());

    return second_camera;
}

void Renderer3D::render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox)
{
    Camera3D* second_camera = create_second_camera(camera);
    vector<Camera3D*> cameras = vector<Camera3D*>();
    cameras.push_back(camera);
    // cameras.push_back(camera);
    cameras.push_back(second_camera);

    GLuint half_width = this->get_width() / 2;

    for(int i = 0; i < cameras.size(); i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffers[i]);
        glViewport(0, 0, this->get_width() / 2, this->get_height()); 
        this->clear();

        if (skybox != NULL)
            skybox->draw(cameras[i]->get_view_transform(), cameras[i]->get_perpective_projection());
        for (ShaderProgram* shader : shaders)
        {
            shader->use_program();

            this->set_lighting(shader, lights); // TODO: investigate 1282 error
            this->set_camera(shader, cameras[i]); // TODO: investigate 1282 error

            this->draw_objects(world_root, shader);
        }
    }

    this->draw_frame_buffer(this->rendered_texture);
    this->quads[0]->draw(rendered_textures[0]);
    this->quads[1]->draw(rendered_textures[1]);
    glfwSwapBuffers(this->get_window());

    free(second_camera);
}