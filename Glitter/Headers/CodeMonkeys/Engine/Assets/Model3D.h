#pragma once

#include <vector>
#include <string>
#include "ModelLoader.h"
#include "Glitter.hpp"

using namespace std;

namespace CodeMonkeys::TheGauntlet::Engine::Assets
{
    // Represents a 3D model with its textures and shaders.
    class Model3D
    {
    private:
        vector<VAO*> vaos;
        mlModel* ml_model;
        vector<Texture*> textures;
        vector<ShaderProgram*> shaders;

    public:
        Model3D(mlModel* ml_model, vector<Texture*> textures, vector<ShaderProgram*> shaders);
        // Render the Model3D using its model, textures, and shaders.
        void draw();
    };
};