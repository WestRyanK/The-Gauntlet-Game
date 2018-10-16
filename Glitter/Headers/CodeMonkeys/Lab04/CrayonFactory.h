#pragma once

#include <vector>
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"
#include "CodeMonkeys/Engine/Assets/ShaderHelpers.h"
#include "glitter.hpp"

using namespace std;
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::Lab04
{
    class CrayonFactory
    {
    private:
        static vector<Texture*> textures;
        static vector<ShaderProgram> shaders;
        static PhysicalObject3D* load_model(std::string file_name, std::string texture_name, Texture* texture, std::string name);
    public:
        static PhysicalObject3D* create_crayon();
        static PhysicalObject3D* create_crayon_box();
        static void init(vector<Texture*> textures, vector<ShaderProgram> shaders);
    };
}