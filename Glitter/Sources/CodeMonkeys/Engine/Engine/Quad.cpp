#include "CodeMonkeys/Engine/Engine/Quad.h"

using CodeMonkeys::Engine::Engine::Quad;


ShaderProgram* Quad::quad_shader = NULL;

Quad::Quad(float x, float y, float width, float height)
{
    if (Quad::quad_shader == NULL)
        Quad::quad_shader = new ShaderProgram("Shaders/frame_buffer.vert", "Shaders/frame_buffer.frag");

    // The fullscreen quad's FBO
    glGenVertexArrays(1, &this->quad_vao);
    glBindVertexArray(this->quad_vao);

    const GLfloat quad_vertex_buffer_data[] = {
        x, y,                   0.0f, 0.0f,
        x + width, y,           1.0f, 0.0f,
        x,  y + height,         0.0f, 1.0f,
        x,  y + height,         0.0f, 1.0f,
        x + width, y,           1.0f, 0.0f,
        x + width,  y + height, 1.0f, 1.0f
    };

    GLuint quad_vbo;
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex_buffer_data), quad_vertex_buffer_data, GL_STATIC_DRAW);

    // 1st attribute buffer : vertices
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(
    //     0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    //     3,                  // size
    //     GL_FLOAT,           // type
    //     GL_FALSE,           // normalized?
    //     0,                  // stride
    //     (void*)0            // array buffer offset
    // );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);
}

void Quad::draw(GLuint rendered_texture)
{ 
    Quad::quad_shader->use_program();

    // // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rendered_texture);
    // // Set our "renderedTexture" sampler to use Texture Unit 0
    GLuint quad_texture_id = glGetUniformLocation(this->quad_shader->get_shader_id(), "rendered_texture");
    glUniform1i(quad_texture_id, 0);
    // this->quad_shader->setUniform("rendered_texture", (int)rendered_texture);

    glBindVertexArray(this->quad_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6); 

    glBindVertexArray(0);
    // glBindTexture(GL_TEXTURE_2D, 0);
}