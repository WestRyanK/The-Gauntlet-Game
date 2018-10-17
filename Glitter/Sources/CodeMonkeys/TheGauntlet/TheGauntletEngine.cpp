#include <vector>
#include "CodeMonkeys/Engine/Objects/AmbientLight.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/DirectionalLight.h"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
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
using namespace CodeMonkeys::Engine::Assets;

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
    ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
    // Make sure that every shader used in the scene is added to the engine's list of shaders so
    // that lighting can be calculated.
    this->shaders.insert(shader);
    CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::init_asteroid_factory(0, shader);
    CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::init(shader);

    // Draw Asteroid
    // Asteroid* asteroid = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid(3);
    // this->world_root->add_child(asteroid);

    // Draw test subdivided shape
    // vector<Material*> mats;
    // mats.push_back(new ColorMaterial(shader, true, 1.0f, vec3(1.0f), vec3(0.2f)));
    // mlModel* model = CodeMonkeys::Engine::Assets::LoopSubdivider::test();
    // auto model3d = new Model3D(model, mats);
    // auto obj3d = new PhysicalObject3D(model3d, "test object");
    // obj3d->set_angular_velocity(vec3(0.0f, 0.5f, 0.0f));
    // this->world_root->add_child(obj3d);


    // Draw Crayon and Box
    CodeMonkeys::Lab04::CrayonFactory::init(shader);
    PhysicalObject3D* crayon = CodeMonkeys::Lab04::CrayonFactory::create_crayon();
    PhysicalObject3D* box = CodeMonkeys::Lab04::CrayonFactory::create_crayon_box();
    box->set_angular_velocity(vec3(0.0f, 0.5f, 0.0f));
    this->world_root->add_child(crayon);
    this->world_root->add_child(box);

    this->camera = new Camera3D();

    auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(this->camera, this->get_window());
    // auto mouse_controller = new CodeMonkeys::TheGauntlet::Control::MouseController(ship, this->get_window());
    this->controllers.insert(keyboard_controller);

    AmbientLight* ambient = new AmbientLight(vec3(1.0f, 1.0f, 1.0f), 0.3f);
    this->lights.insert(ambient);

    DirectionalLight* directional = new DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.6f, vec3(0.0f, -1.0f, -1.0f));
    this->lights.insert(directional);

    // DirectionalLight* directional2 = new DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.2f, vec3(0.0f, 1.0f, 1.0f));
    // this->lights.insert(directional2);
}