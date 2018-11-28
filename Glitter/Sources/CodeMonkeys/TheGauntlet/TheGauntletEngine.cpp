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
#include "CodeMonkeys/Engine/Collision/GridCollisionDetector.h"
#include "CodeMonkeys/Engine/Collision/SimpleCollisionDetector.h"
#include "CodeMonkeys/TheGauntlet/Collision/ShipAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/Collision/ProjectileAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/Collision/AsteroidAsteroidCollisionResponse.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/Engine/Objects/BillboardParticle.h"
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
    ShaderProgram* skybox_shader = new ShaderProgram("Shaders/skybox.vert", "Shaders/skybox.frag");
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
    this->skybox = new Skybox(skybox_faces, skybox_shader);
}

void TheGauntletEngine::init_light_and_camera(Object3D* camera_parent)
{
    SpringArm* spring_arm = new SpringArm(10.0f, 1.0f, 1.0f);
    this->camera = new Camera3D();
    camera_parent->add_child(spring_arm);
    spring_arm->add_child(this->camera);
    this->camera->set_look_at(camera_parent);

    AmbientLight* ambient = new AmbientLight(vec3(1.0f, 1.0f, 1.0f), 0.3f);
    this->lights.insert(ambient);

    DirectionalLight* directional = new DirectionalLight(vec3(1.0f, 1.0f, 1.0f), 0.6f, vec3(-1, -1, 0));
    this->lights.insert(directional);
}

void TheGauntletEngine::init()
{
    this->set_collision_detector(new GridCollisionDetector(vec3(1000), vec3(-1000), 50)); // this->set_collision_detector(new SimpleCollisionDetector());

    ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
    // Make sure that every shader used in the scene is added to the engine's list of shaders so
    // that lighting can be calculated.
    this->shaders.insert(shader);
    Billboard::init_billboard_class();
    this->shaders.insert(Billboard::get_shader());
    CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::init_asteroid_factory(0, shader);
    ParticleEmitter* projectile_emitter = new ParticleEmitter("projectile_emitter");
    this->world_root->add_child(projectile_emitter);
    CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::init(shader, projectile_emitter);
    this->init_skybox();
    

    auto ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_x_wing_ship();
    this->world_root->add_child(ship);


    // Draw Asteroid
    // const int S = 800;
    // const int T = 800;
    // const int V = 25;
    // const int A = 60;
    // for (int i = 0; i < 2000; i++)
    // {
    //     Asteroid* asteroid = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid_random_size();
    //     this->world_root->add_child(asteroid);
    //     // asteroid->set_position(vec3(rand() % T - T / 2, 0, rand() % S - S));
    //     asteroid->set_position(vec3(rand() % T - T / 2, rand() % T - T / 2, rand() % S - S));
    //     // asteroid->set_velocity(vec3(rand() % V - V / 2, 0, rand() % V - V / 2));
    //     asteroid->set_velocity(vec3(rand() % V - V / 2, rand() % V - V / 2, rand() % V - V / 2));
    //     asteroid->set_angular_velocity(vec3(rand() % A - A / 2, rand() % A - A / 2, rand() % A - A / 2));
    // }

    Asteroid* asteroid = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid(1);
    this->world_root->add_child(asteroid);
    asteroid->set_position(vec3(40, 0, 40));
    asteroid->set_angular_velocity(vec3(40));

    Asteroid* asteroi2 = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid(3);
    this->world_root->add_child(asteroi2);
    asteroi2->set_position(vec3(-40, 0, -40));
    asteroi2->set_velocity(vec3(0, 1, 0));
    asteroi2->set_angular_velocity(vec3(-40));


    this->init_light_and_camera(ship);
    // auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(this->camera, this->get_window());
    auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(ship, this->get_window());
    this->controllers.insert(keyboard_controller);

    this->collision_responses.insert(new ShipAsteroidCollisionResponse(this));
    this->collision_responses.insert(new AsteroidAsteroidCollisionResponse(this));
    this->collision_responses.insert(new ProjectileAsteroidCollisionResponse(this));

    this->renderer = new Renderer(this->get_window(), this->get_width(), this->get_height());
    // this->renderer = new FrameBufferRenderer(this->get_window(), this->get_width(), this->get_height());
    // this->renderer = new Renderer3D(this->get_window(), this->get_width(), this->get_height(), 2);
}
