#include <vector>
#include <stdlib.h>
#include "CodeMonkeys/Engine/Objects/AmbientLight.h"
#include "CodeMonkeys/Engine/Objects/SpringArm.h"
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

    auto ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_x_wing_ship();
    this->world_root->add_child(ship);

    // Draw Asteroid
    const int S = 2000;
    const int T = 400;
    for (int i = 0; i < 2000; i++)
    {
        Asteroid* asteroid = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid_random_size();
        this->world_root->add_child(asteroid);
        asteroid->set_position(vec3(rand() % T - T / 2, rand() % T - T / 2, rand() % S - S));
    }

    // Draw test subdivided shape
    // vector<Material*> mats;
    // mats.push_back(new ColorMaterial(shader, true, 1.0f, vec3(1.0f), vec3(1.0f)));
    // mlModel* model = CodeMonkeys::Engine::Assets::LoopSubdivider::test();
    // auto model3d = new Model3D(model, mats);
    // auto obj3d = new PhysicalObject3D(model3d, "test object");
    // obj3d->set_angular_velocity(vec3(0.5f, 0.0f, 0.0f));
    // // obj3d->set_velocity(vec3(0.0f, 0.5f, 0.0f));
    // this->world_root->add_child(obj3d);

    // Draw Crayon and Box
    CodeMonkeys::Lab04::CrayonFactory::init(shader);
    PhysicalObject3D* crayon = CodeMonkeys::Lab04::CrayonFactory::create_crayon();
    PhysicalObject3D* box = CodeMonkeys::Lab04::CrayonFactory::create_crayon_box();
    box->set_position(vec3(0.0f, 10.0f, 0.0f));
    box->set_angular_velocity(vec3(0.0f, 0.5f, 0.0f));
    crayon->set_angular_velocity(vec3(0.0f, 0.5f, 0.0f));
    this->world_root->add_child(crayon);
    this->world_root->add_child(box);

    SpringArm* spring_arm = new SpringArm(10.0f, 1.0f, 1.0f);
    this->camera = new Camera3D();
    ship->add_child(spring_arm);
    // ship->add_child(this->camera);
    spring_arm->add_child(this->camera);
    this->camera->set_look_at(ship);

    auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(ship, this->get_window());
    // auto mouse_controller = new CodeMonkeys::TheGauntlet::Control::MouseController(ship, this->get_window());
    this->controllers.insert(keyboard_controller);

    AmbientLight* ambient = new AmbientLight(vec3(1.0f, 1.0f, 1.0f), 0.3f);
    this->lights.insert(ambient);

    DirectionalLight* directional = new DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.6f, vec3(-1, -1, 0));
    this->lights.insert(directional);

    // DirectionalLight* directional2 = new DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.2f, vec3(0.0f, 1.0f, 1.0f));
    // this->lights.insert(directional2);
}