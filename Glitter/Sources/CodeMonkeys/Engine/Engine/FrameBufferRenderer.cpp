#include "CodeMonkeys/Engine/Engine/FrameBufferRenderer.h"

using CodeMonkeys::Engine::Engine::FrameBufferRenderer;


FrameBufferRenderer::FrameBufferRenderer(GLFWwindow* window, GLuint width, GLuint height) : Renderer(window, width, height)
{
    this->create_frame_buffer(this->get_width(), this->get_height(), this->frame_buffer, this->rendered_texture);
    this->create_output_quad();
}

void FrameBufferRenderer::create_output_quad()
{
    // The fullscreen quad's FBO
    glGenVertexArrays(1, &this->quad_vao);
    glBindVertexArray(this->quad_vao);

    static const GLfloat quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };

    GLuint quad_vbo;
    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex_buffer_data), quad_vertex_buffer_data, GL_STATIC_DRAW);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glBindVertexArray(0);

    // Create and compile our GLSL program from the shaders
    // this->quad_shader = new ShaderProgram("Shaders/frame_buffer.vert", "Shaders/frame_buffer.frag");
    // this->quad_shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
}

void FrameBufferRenderer::set_frame_buffer(GLuint frame_buffer, GLuint x, GLuint y, GLuint width, GLuint height)
{
    // Render to our framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    glViewport(x, y, width, height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}

void FrameBufferRenderer::draw_frame_buffer(GLuint rendered_texture)
{ 
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, this->get_width(), this->get_height()); 
    // // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // // Use our shader
    this->quad_shader->use_program();

    // // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rendered_texture);
    // // Set our "renderedTexture" sampler to use Texture Unit 0
    // this->quad_texture_id = glGetUniformLocation(this->quad_shader->get_shader_id(), "rendered_texture");
    this->quad_shader->setUniform("rendered_texture", (int)rendered_texture);
    // glUniform1i(this->quad_texture_id, 0);

    glBindVertexArray(this->quad_vao);
    // // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBufferRenderer::create_frame_buffer(GLuint width, GLuint height, GLuint& frame_buffer, GLuint& rendered_texture)
{
    frame_buffer = 0;
    glGenFramebuffers(1, &frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

    // The texture we're going to render to
    glGenTextures(1, &rendered_texture);
    glBindTexture(GL_TEXTURE_2D, rendered_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    // Set "rendered_texture" as our colour attachement #0
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rendered_texture, 0);

    // The depth buffer
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // Set the list of draw buffers.
    GLenum draw_buffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, draw_buffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("Failed to load framebuffer!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#include <fstream>
void screenshot (char filename[160],int x, int y)
{
    // get the image data
    long imageSize = x * y * 3;
    unsigned char *data = new unsigned char[imageSize];
    glReadPixels(0,0,x,y, GL_BGR,GL_UNSIGNED_BYTE,data);// split x and y sizes into bytes
    int xa= x % 256;
    int xb= (x-xa)/256;int ya= y % 256;
    int yb= (y-ya)/256;//assemble the header
    unsigned char header[18]={0,0,2,0,0,0,0,0,0,0,0,0,(char)xa,(char)xb,(char)ya,(char)yb,24,0};
    // write header and data to file
    fstream File(filename, ios::out | ios::binary);
    File.write (reinterpret_cast<char *>(header), sizeof (char)*18);
    File.write (reinterpret_cast<char *>(data), sizeof (char)*imageSize);
    File.close();

    delete[] data;
    data=NULL;
}

void FrameBufferRenderer::render(set<ShaderProgram*> shaders, set<ILight3D*> lights, Camera3D* camera, Object3D* world_root, Skybox* skybox)
{
    // this->set_frame_buffer(this->frame_buffer, 0, 0, this->get_width(), this->get_height());

    this->clear();
    this->set_lighting(shaders, lights); // TODO: investigate 1282 error
    this->set_camera(shaders, camera); // TODO: investigate 1282 error
    // "action!"
    if (skybox != NULL)
        skybox->draw(camera->get_view_transform(), camera->get_perpective_projection());

    this->draw_objects(world_root);

    screenshot("test.tga", this->get_width(), this->get_height());
    // this->draw_frame_buffer(this->rendered_texture);
    glfwSwapBuffers(this->get_window());
}
