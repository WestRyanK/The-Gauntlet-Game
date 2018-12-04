#include "CodeMonkeys/TheGauntlet/GameObjects/PortalFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Portal.h"
#include "CodeMonkeys/Engine/Assets/Model3D.h"
#include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Assets/TextureMaterial.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"
#include <vector>

using CodeMonkeys::TheGauntlet::GameObjects::PortalFactory;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::Assets;

vector<Material*> PortalFactory::materials = vector<Material*>();

void PortalFactory::init(ShaderProgram* shader)
{
    //auto texture = new Texture("Assets/Textures/portal-texture.jpg");
    //Material* material = new TextureMaterial(shader, false, 1.0f, vec3(1.0f, 1.0f, 1.0f), texture);
    Material* material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(0.6f, 0.6f, 0.9f));
    vector<Material*> materials;
    materials.push_back(material);
    PortalFactory::materials = materials;
}

Portal* PortalFactory::create_portal()
{
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Other/", "portal.obj", *ml_model);
    Model3D* model = new Model3D(ml_model, PortalFactory::materials);
    Portal* portal = new Portal(model);
    return portal;
}