#include "CodeMonkeys/Lab04/CrayonFactory.h"
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include <string>

using CodeMonkeys::Lab04::CrayonFactory;
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;
using namespace std;

vector<Texture*> CrayonFactory::textures = vector<Texture*>();
vector<ShaderProgram> CrayonFactory::shaders = vector<ShaderProgram>();

PhysicalObject3D* CrayonFactory::create_crayon()
{
    return CrayonFactory::load_model("crayon.obj", "Assets/Lab04/Crayon Texture.png", CrayonFactory::textures[0], "Crayon");
}

PhysicalObject3D* CrayonFactory::create_crayon_box()
{
    return CrayonFactory::load_model("box.obj", "Assets/Lab04/box_texture2.png", CrayonFactory::textures[1], "Crayon Box");
}

void CrayonFactory::init(vector<Texture*> textures, vector<ShaderProgram> shaders)
{
    CrayonFactory::textures = textures;
    CrayonFactory::shaders = shaders;
}


PhysicalObject3D* CrayonFactory::load_model(std::string file_name, std::string texture_name, Texture* texture, std::string name)
{
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Lab04", file_name, *ml_model);

    vector<Texture*> t;
    t.push_back(texture);
    Model3D* model = new Model3D(ml_model, t, shaders);
    PhysicalObject3D* object = new PhysicalObject3D(model, name);

    return object;
}