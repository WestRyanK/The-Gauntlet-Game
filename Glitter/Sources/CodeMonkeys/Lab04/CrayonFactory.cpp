#include "CodeMonkeys/Lab04/CrayonFactory.h"
#include "CodeMonkeys/Engine/Assets/Material.h"
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Assets/TextureMaterial.h"
#include <string>

using CodeMonkeys::Lab04::CrayonFactory;
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;
using namespace std;

Material* CrayonFactory::crayon_material = NULL;
Material* CrayonFactory::box_material = NULL;

PhysicalObject3D* CrayonFactory::create_crayon()
{
    return CrayonFactory::load_model("crayon.obj", CrayonFactory::crayon_material, "Crayon");
}

PhysicalObject3D* CrayonFactory::create_crayon_box()
{
    return CrayonFactory::load_model("box.obj", CrayonFactory::box_material, "Crayon Box");
}

void CrayonFactory::init(ShaderProgram* shader)
{
    Texture* crayon_texture = new Texture("Assets/Lab04/crayon_texture.png");
    Texture* box_texture = new Texture("Assets/Lab04/box_texture.png");
    CrayonFactory::crayon_material = new TextureMaterial(shader, true, 1.0f, vec3(1.0f), crayon_texture);
    CrayonFactory::box_material = new TextureMaterial(shader, true, 1.0f, vec3(1.0f), box_texture);
}


PhysicalObject3D* CrayonFactory::load_model(std::string file_name, Material* material, std::string name)
{
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Lab04", file_name, *ml_model);

    vector<Material*> m;
    m.push_back(material);
    Model3D* model = new Model3D(ml_model, m);
    PhysicalObject3D* object = new PhysicalObject3D(model, name);

    return object;
}