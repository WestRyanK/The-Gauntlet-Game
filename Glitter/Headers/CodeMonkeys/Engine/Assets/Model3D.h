#pragma once

#include <vector>
#include <string>
#include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"
#include "glitter.hpp"

using namespace std;

namespace CodeMonkeys::Engine::Assets
{
    // Represents a 3D model with its textures and shaders.
    class Model3D
    {
    private:
        const static int POSITION_INDEX = 0;
        const static int NORMAL_INDEX = 1;
        const static int UV_INDEX = 2;

        const static unsigned int POSITION_SIZE = 3;
        const static unsigned int NORMAL_SIZE = 3;
        const static unsigned int UV_SIZE = 2;
        const static unsigned int VERTEX_SIZE = POSITION_SIZE + NORMAL_SIZE + UV_SIZE;

        vector<unsigned int> ebos;
        vector<unsigned int> ebo_sizes;
        vector<VAO> vaos;
        mlModel* ml_model;
        vector<Texture*> textures;
        vector<ShaderProgram> shaders;

        void create_ebo(mlMesh mesh);
        void create_vao(mlMesh mesh);
        float* convert_mesh_to_vertices(mlMesh mesh);

    public:
        Model3D(mlModel* ml_model, vector<Texture*> textures, vector<ShaderProgram> shaders);
        // Render the Model3D using its model, textures, and shaders.
        void draw();
    };
};