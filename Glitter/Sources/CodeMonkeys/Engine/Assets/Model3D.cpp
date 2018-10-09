#include "Model3D.h"
#include "NIE.h"

using CodeMonkeys::Engine::Assets::Model3D;

Model3D::Model3D(mlModel* ml_model, vector<Texture*> textures, vector<ShaderProgram> shaders)
{
    // Here we should disect the mlModel and create VAOs for each of the meshes
    for (int i = 0; i < ml_model->meshes.size(); i++)
    {
        this->create_vao(ml_model->meshes[i]);
        this->create_ebo(ml_model->meshes[i]);
    }
    
    this->textures = textures;
    this->shaders = shaders;
    // throw NotImplementedException("Model3D::constructor");
}

void Model3D::create_ebo(mlMesh mesh) 
{
    unsigned int* indices = new unsigned int[mesh.indices.size()];
    for (int i = 0; i < mesh.indices.size(); i++)
    {
        indices[i] = mesh.indices[i];
    }

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size(), indices, GL_STATIC_DRAW); 

    this->ebos.push_back(ebo);
    this->ebo_sizes.push_back(mesh.indices.size());
}

void Model3D::create_vao(mlMesh mesh)
{
    float* vertices = Model3D::convert_mesh_to_vertices(mesh);

    VAO vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * VERTEX_SIZE, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(POSITION_INDEX, POSITION_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)0);
    glEnableVertexAttribArray(POSITION_INDEX);
    glVertexAttribPointer(NORMAL_INDEX, NORMAL_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)(POSITION_SIZE * sizeof(float)));
    glEnableVertexAttribArray(NORMAL_INDEX);
    glVertexAttribPointer(UV_INDEX, UV_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), (void*)((POSITION_SIZE + NORMAL_SIZE) * sizeof(float)));
    glEnableVertexAttribArray(UV_INDEX);

    glBindVertexArray(0);

    this->vaos.push_back(vao);
}

float* Model3D::convert_mesh_to_vertices(mlMesh mesh)
{
    float* vertices = new float[mesh.vertices.size() * VERTEX_SIZE];
    int offset = 0;
    for (int i = 0; i < mesh.vertices.size(); i++)
    {
        // Insert the position into the vertex array.
        for (int j = 0; j < POSITION_SIZE; j++)
        {
            vertices[j + offset] = mesh.vertices[i].position[j];
        }

        // Insert the normal into the vertex array.
        offset += POSITION_SIZE;
        for (int j = 0; j < NORMAL_SIZE; j++)
        {
            vertices[j + offset] = mesh.vertices[i].normal[j];
        }

        // Insert the UV into the vertex array.
        offset += NORMAL_SIZE;
        for (int j = 0; j < UV_SIZE; j++)
        {
            vertices[j + offset] = mesh.vertices[i].UV[j];
        }
        offset += UV_SIZE;
    }

    return vertices;
}

void Model3D::draw()
{
    for (int i = 0; i < this->vaos.size(); i++)
    {
        glUseProgram(this->shaders[i]);

        glBindVertexArray(this->vaos[i]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebos[i]);
        glDrawElements(GL_TRIANGLES, this->ebo_sizes[i], GL_UNSIGNED_INT, 0);
    }
}