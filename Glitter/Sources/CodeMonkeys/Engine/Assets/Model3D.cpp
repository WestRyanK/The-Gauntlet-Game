#include "Model3D.h"
#include "NIE.h"

using CodeMonkeys::Engine::Assets::Model3D;

Model3D::Model3D(mlModel* ml_model, vector<Texture*> textures, vector<ShaderProgram> shaders)
{
    // Here we should disect the mlModel and create VAOs for each of the meshes
    
    this->textures = textures;
    this->shaders = shaders;
    throw NotImplementedException("Model3D::constructor");
}

void Model3D::draw()
{
    throw NotImplementedException("Model3D::draw");
}