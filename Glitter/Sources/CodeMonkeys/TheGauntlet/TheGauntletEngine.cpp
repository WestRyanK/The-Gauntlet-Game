#include <vector>
#include "CodeMonkeys/Engine/Objects/AmbientLight.h"
#include "CodeMonkeys/Engine/Objects/DirectionalLight.h"
#include "CodeMonkeys/Engine/Assets/ShaderHelpers.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletEngine.h"
#include "CodeMonkeys/Lab04/CrayonFactory.h"
#include "CodeMonkeys/TheGauntlet/Control/KeyboardController.h"
#include "CodeMonkeys/TheGauntlet/Control/MouseController.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/ShipFactory.h"
#include "CodeMonkeys/Engine/Assets/LoopSubdivider.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/AsteroidFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"

using namespace std;
using CodeMonkeys::TheGauntlet::TheGauntletEngine;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::Engine::Objects;

TheGauntletEngine::TheGauntletEngine(GLFWwindow* window) : GameEngine(window)
{
}

void TheGauntletEngine::update_frame(float dt)
{
    this->handle_controllers(dt);
    this->update_objects(dt);
    this->handle_collisions(dt);
    this->draw();
}

void TheGauntletEngine::init()
{
    vector<ShaderProgram> shaders;
    vector<Texture*> textures;
    ShaderProgram shader = CodeMonkeys::Engine::Assets::LoadShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
    shaders.push_back(shader);
    this->shaders.insert(shader);
    CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::init_asteroid_factory(0, shaders, textures);
    CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::init(shaders, textures);

    Asteroid* asteroid = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid(3);
    this->world_root->add_child(asteroid);

    mlModel* ml_model = CodeMonkeys::Engine::Assets::LoopSubdivider::test();
    Model3D* subdivided = new Model3D(ml_model, textures, shaders);
    Object3D* obj = new Object3D(subdivided, "Subdivided");
    this->world_root->add_child(obj);

    textures.push_back(new Texture("Assets/Lab04/crayon_texture.png"));
    textures.push_back(new Texture("Assets/Lab04/box_texture.png"));

    CodeMonkeys::Lab04::CrayonFactory::init(textures, shaders);
    PhysicalObject3D* crayon = CodeMonkeys::Lab04::CrayonFactory::create_crayon();
    PhysicalObject3D* box = CodeMonkeys::Lab04::CrayonFactory::create_crayon_box();
    box->set_rotation(vec3(0.0f, 25.0f, 0.0f));
    this->world_root->add_child(crayon);
    this->world_root->add_child(box);

    this->camera = new Camera3D();

    auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(this->camera, this->get_window());
    // auto mouse_controller = new CodeMonkeys::TheGauntlet::Control::MouseController(ship, this->get_window());
    this->controllers.insert(keyboard_controller);

    AmbientLight* ambient = new AmbientLight(vec3(1.0f, 1.0f, 1.0f), 0.2f);
    this->lights.insert(ambient);

    DirectionalLight* directional = new DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.2f, vec3(1.0f, 1.0f, 0.0f));
    this->lights.insert(directional);

    DirectionalLight* directional2 = new DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.6f, vec3(0.0f, 1.0f, 1.0f));
    this->lights.insert(directional2);
}