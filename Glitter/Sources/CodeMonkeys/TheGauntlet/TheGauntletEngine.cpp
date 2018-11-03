#include <vector>
#include <stdlib.h>
#include "CodeMonkeys/Engine/Objects/AmbientLight.h"
#include "CodeMonkeys/Engine/Engine/Renderer3D.h"
#include "CodeMonkeys/Engine/Objects/SpringArm.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/DirectionalLight.h"
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletEngine.h"
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

TheGauntletEngine::TheGauntletEngine(GLFWwindow* window, GLuint width, GLuint height) : GameEngine(window, width, height)
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
    ShaderProgram* skyboxShader = new ShaderProgram("Shaders/skybox.vert", "Shaders/skybox.frag");
    // Make sure that every shader used in the scene is added to the engine's list of shaders so
    // that lighting can be calculated.
    this->shaders.insert(shader);
    CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::init_asteroid_factory(0, shader);
    CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::init(shader);
    
    // create skybox
    std::vector<std::string> skybox_faces
    {
        "Assets/Textures/Skybox/right.png",
        "Assets/Textures/Skybox/left.png",
        "Assets/Textures/Skybox/top.png",
        "Assets/Textures/Skybox/bottom.png",
        "Assets/Textures/Skybox/front.png",
        "Assets/Textures/Skybox/back.png"
    };
    this->skybox = new Skybox(skybox_faces, skyboxShader);

    auto ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_x_wing_ship();
    this->world_root->add_child(ship);

    // Draw Asteroid
    const int S = 2000;
    const int T = 400;
    const int V = 50;
    const int A = 5;
    for (int i = 0; i < 2000; i++)
    {
        Asteroid* asteroid = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid_random_size();
        this->world_root->add_child(asteroid);
        asteroid->set_position(vec3(rand() % T - T / 2, rand() % T - T / 2, rand() % S - S));
        asteroid->set_velocity(vec3(rand() % V - V / 2, rand() % V - V / 2, rand() % V - V / 2));
        asteroid->set_angular_velocity(vec3(rand() % A - A / 2, rand() % A - A / 2, rand() % A - A / 2));
    }

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

    // this->renderer = new FrameBufferRenderer(this->get_window(), 1280, 480);
    this->renderer = new Renderer3D(this->get_window(), this->get_width(), this->get_height(), 6);
}
