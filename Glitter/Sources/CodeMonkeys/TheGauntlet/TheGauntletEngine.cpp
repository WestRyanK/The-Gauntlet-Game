#include "CodeMonkeys/Engine/Assets/ShaderHelpers.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletEngine.h"
#include "CodeMonkeys/TheGauntlet/Control/KeyboardController.h"
#include "CodeMonkeys/TheGauntlet/Control/MouseController.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/ShipFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/AsteroidFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"

using CodeMonkeys::TheGauntlet::TheGauntletEngine;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

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

    auto ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_x_wing_ship();
    ship->set_velocity(vec4(0.0f, 5.0f, 0.0f, 1.0f));
    ship->set_angular_velocity(vec4(0.0f, 5.0f, 0.0f, 1.0f));
    this->world_root->add_child(ship);

    this->camera = new Camera3D();

    auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(this->camera, this->get_window());
    // auto mouse_controller = new CodeMonkeys::TheGauntlet::Control::MouseController(ship, this->get_window());
    this->controllers.insert(keyboard_controller);

    Asteroid* asteroid = AsteroidFactory::create_asteroid(3);
    this->world_root->add_child(asteroid);
}