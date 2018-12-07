#include <vector>
#include <stdlib.h>
#include <SFML/Audio.hpp>
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
#include "CodeMonkeys/TheGauntlet/GameObjects/Portal.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/PortalFactory.h"
#include "CodeMonkeys/Engine/Collision/GridCollisionDetector.h"
#include "CodeMonkeys/Engine/Collision/SimpleCollisionDetector.h"
#include "CodeMonkeys/TheGauntlet/Collision/ShipAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/Collision/ShipPortalCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/Collision/ProjectileAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/Collision/AsteroidAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/UI/HealthBar.h"
#include "CodeMonkeys/TheGauntlet/UI/RechargeBar.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"

using namespace std;
using CodeMonkeys::TheGauntlet::TheGauntletEngine;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::TheGauntlet::Collision;
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
    printf("\n");
}

void TheGauntletEngine::init_skybox()
{
    auto skybox_shader = new ShaderProgram("Assets/Shaders/skybox.vert", "Assets/Shaders/skybox.frag");
    std::vector<std::string> skybox_faces
    {
        "Assets/Skybox/right.png",
        "Assets/Skybox/left.png",
        "Assets/Skybox/top.png",
        "Assets/Skybox/bottom.png",
        "Assets/Skybox/front.png",
        "Assets/Skybox/back.png"
    };
    this->skybox = new Skybox(skybox_faces, skybox_shader);
}

void TheGauntletEngine::init_light_and_camera(Object3D* camera_parent)
{
    auto spring_arm = new SpringArm(10.0f, 1.0f, 1.0f);
    this->camera = new Camera3D();
    camera_parent->add_child(spring_arm);
    spring_arm->add_child(this->camera);
    this->camera->set_look_at(camera_parent);

    auto ambient = new AmbientLight(vec3(1.0f, 1.0f, 1.0f), 0.3f);
    this->lights.insert(ambient);

    auto directional = new DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.6f, vec3(-1, -1, 0));
    this->lights.insert(directional);
}

void TheGauntletEngine::init()
{
    auto music = new sf::Music();
    if (!music->openFromFile("Assets/Music/system_shock.wav"))
        printf("Could not load 'system_shock.wav' file!\n");
    music->setLoop(true);
    music->setVolume(30.0f);
    music->play();

    this->set_collision_detector(new GridCollisionDetector(vec3(1000), vec3(-1000), 50)); // this->set_collision_detector(new SimpleCollisionDetector());

    auto shader = new ShaderProgram("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
    auto projectile_shader = new ShaderProgram("Assets/Shaders/basic.vert", "Assets/Shaders/self_illuminated.frag");

    CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::init_asteroid_factory(0, shader);
    CodeMonkeys::TheGauntlet::GameObjects::Asteroid::init(this->world_root);
    CodeMonkeys::TheGauntlet::GameObjects::PortalFactory::init(shader);

    ParticleEmitter* projectile_emitter = new ParticleEmitter("projectile_emitter");
    this->world_root->add_child(projectile_emitter);
    CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::init(shader, projectile_emitter, projectile_shader);

    // Make sure that every shader used in the scene is added to the engine's list of shaders so
    // that lighting can be calculated.
    this->shaders.insert(shader);
    this->shaders.insert(projectile_shader);
    Billboard::init_billboard_class();
    this->shaders.insert(Billboard::get_shader());

    this->init_skybox();

    // auto ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_jet_fighter();
    auto ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_x_wing_ship();
    // auto ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_crayon_ship();
    this->world_root->add_child(ship);

    setup_course();

    auto health_bar = new HealthBar(ship, -1, 0.65, 0.75f, 0.40f);
    this->quads.insert(health_bar);

    if (ship->get_secondary_weapon() != NULL)
    {
        auto recharge_bar = new RechargeBar(ship->get_secondary_weapon(), -1, 0.45f, 0.75f, 0.40f);
        this->quads.insert(recharge_bar);
    }

    this->init_light_and_camera(ship);
    auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(ship, this->get_window());
    this->controllers.insert(keyboard_controller);

    this->collision_responses.insert(new ShipAsteroidCollisionResponse(this));
    this->collision_responses.insert(new AsteroidAsteroidCollisionResponse(this));
    this->collision_responses.insert(new ProjectileAsteroidCollisionResponse(this));
    this->collision_responses.insert(new ShipPortalCollisionResponse(this));

    // this->renderer = new Renderer(this->get_window(), this->get_width(), this->get_height());
    this->renderer = new FrameBufferRenderer(this->get_window(), this->get_width() * 2, this->get_height() * 2);
    // this->renderer = new Renderer3D(this->get_window(), this->get_width(), this->get_height(), 2);
}

void TheGauntletEngine::setup_course() {
    const int S = 4000;
    const int T = 400;
    const int V = 100;
    const int A = 60;
    for (int i = 0; i < 500; i++)
    {
        Asteroid* asteroid = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid_random_size();
        this->world_root->add_child(asteroid);
        asteroid->set_position(vec3(rand() % T - T / 2, rand() % T - T / 2, rand() % S - S));
        asteroid->set_velocity(vec3(rand() % V - V / 2, rand() % V - V / 2, rand() % V - V / 2));
        asteroid->set_angular_velocity(vec3(rand() % A - A / 2, rand() % A - A / 2, rand() % A - A / 2));
    }

    auto checker = new BoundaryChecker(T, T, -S, -T, -T, 0);
    this->set_boundary_checker(checker);

    // Draw Portal
    auto portal = CodeMonkeys::TheGauntlet::GameObjects::PortalFactory::create_portal();
    portal->set_position(vec3(0, 0, -S));
    this->world_root->add_child(portal);
}