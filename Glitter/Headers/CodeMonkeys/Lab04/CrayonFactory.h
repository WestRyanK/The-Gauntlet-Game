#pragma once

#include <vector>
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/Engine/Assets/Material.h"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
#include "glitter.hpp"

using namespace std;
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::Lab04
{
    class CrayonFactory
    {
    private:
        static Material* crayon_material;
        static Material* box_material;
        static PhysicalObject3D* load_model(std::string file_name, Material* material, std::string name);
    public:
        static PhysicalObject3D* create_crayon();
        static PhysicalObject3D* create_crayon_box();
        static void init(ShaderProgram* shader);
    };
}