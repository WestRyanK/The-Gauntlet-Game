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
#include "CodeMonkeys/TheGauntlet/Collision/ShipHealthCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/Collision/ProjectileAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/Collision/AsteroidAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/UI/HealthBar.h"
#include "CodeMonkeys/TheGauntlet/UI/ScoreDisplay.h"
#include "CodeMonkeys/TheGauntlet/UI/RechargeBar.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/TheGauntlet/TheGauntletEngineSettings.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Health.h"
#include "CodeMonkeys/Engine/UI/Text.h"

using namespace std;
using CodeMonkeys::TheGauntlet::TheGauntletEngine;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::TheGauntlet::Collision;
using namespace CodeMonkeys::TheGauntlet::UI;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::UI;
using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::Engine::Events;

namespace CodeMonkeys::Engine::Engine { class Renderer3D; }
namespace CodeMonkeys::Engine::Engine { class Renderer; }

TheGauntletEngine::TheGauntletEngine(GLFWwindow* window, GLuint width, GLuint height, TheGauntletEngineSettings* settings) : GameEngine(window, width, height)
// TheGauntletEngine::TheGauntletEngine(GLFWwindow* window, GLuint width, GLuint height) : GameEngine(window, width, height)
{
    this->settings = settings;
    this->game_over = false;
}

void TheGauntletEngine::update_frame(float dt)
{
    this->handle_controllers(dt);
    this->update_objects(dt);
    this->handle_collisions(dt);
    this->draw();
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

void TheGauntletEngine::init_light_and_camera(Ship* camera_parent)
{
    auto spring_arm = new SpringArm(10.0f, 1.0f, 1.0f);
    this->camera = new Camera3D();
    camera_parent->add_child(spring_arm);
    spring_arm->add_child(this->camera);
    this->camera->set_look_at(camera_parent);

    camera_parent->get_crosshairs()->set_camera(this->camera);

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


    auto shader = new ShaderProgram("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
    auto self_illuminated_shader = new ShaderProgram("Assets/Shaders/basic.vert", "Assets/Shaders/self_illuminated.frag");

    CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::init_asteroid_factory(0, shader, this);
    CodeMonkeys::TheGauntlet::GameObjects::Asteroid::init(this->world_root);
    CodeMonkeys::TheGauntlet::GameObjects::PortalFactory::init(self_illuminated_shader);

    ParticleEmitter* projectile_emitter = new ParticleEmitter("projectile_emitter");
    this->world_root->add_child(projectile_emitter);
    CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::init(shader, projectile_emitter, self_illuminated_shader);

    // Make sure that every shader used in the scene is added to the engine's list of shaders so
    // that lighting can be calculated.
    this->shaders.insert(shader);
    this->shaders.insert(self_illuminated_shader);
    Billboard::init_billboard_class();
    this->shaders.insert(Billboard::get_shader());

    this->init_skybox();

    switch (this->settings->get_ship_selection())
    {
        case ShipSelection::SelectionCrayonBox:
            this->ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_crayon_ship();
            break;
        case ShipSelection::SelectionXWingShip:
            this->ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_x_wing_ship();
            break;
        case ShipSelection::SelectionJetFighter:
        default:
            this->ship = CodeMonkeys::TheGauntlet::GameObjects::ShipFactory::create_jet_fighter();
            break;
    }
    this->world_root->add_child(ship);

    setup_course(ship);

    auto health_bar = new HealthBar(ship, vec2(-1, 0.65), vec2(0.75f, 0.40f));
    health_bar->set_alarm_percent(0.35f);
    this->quads.insert(health_bar);

    auto score_display = new ScoreDisplay(this, "score:", vec2(0.45, 0.80f), 0.1);
    score_display->set_character_spacing(0.5f);
    this->quads.insert(score_display);

    if (ship->get_secondary_weapon() != NULL)
    {
        auto recharge_bar = new RechargeBar(ship->get_secondary_weapon(), vec2(-1, 0.45f), vec2(0.75f, 0.40f));
        this->quads.insert(recharge_bar);
    }

    this->init_light_and_camera(ship);
    auto keyboard_controller = new CodeMonkeys::TheGauntlet::Control::KeyboardController(ship, this->get_window());
    auto mouse_controller = new CodeMonkeys::TheGauntlet::Control::MouseController(ship, this->get_window());
    this->controllers.insert(keyboard_controller);
    this->controllers.insert(mouse_controller);

    this->collision_responses.insert(new ShipAsteroidCollisionResponse(this, this));
    this->collision_responses.insert(new ShipHealthCollisionResponse(this, this));
    this->collision_responses.insert(new AsteroidAsteroidCollisionResponse(this));
    this->collision_responses.insert(new ProjectileAsteroidCollisionResponse(this));
    this->collision_responses.insert(new ShipPortalCollisionResponse(this));

    switch (this->settings->get_renderer_selection())
    {
        case RendererSelection::Selection3DRenderer:
            this->renderer = new Renderer3D(this->get_window(), this->get_width(), this->get_height(), 2);
            break;
        case RendererSelection::SelectionFrameRenderer:
            this->renderer = new FrameBufferRenderer(this->get_window(), this->get_width(), this->get_height());
            break;
        default:
            this->renderer = new Renderer(this->get_window(), this->get_width(), this->get_height());
            break;
    }

    this->register_game_events();
}

void TheGauntletEngine::setup_course(Ship* ship) {
    const int S = 4000;
    const int T = 200;
    const int V = 100;
    const int A = 60;
    for (int i = 0; i < 700; i++)
    {
        if (rand() % 100 < 5)
        {
            int healing_value = rand() % 30 + 10;
            Health* health = new Health(healing_value);
            this->world_root->add_child(health);
            health->set_position(vec3(rand() % T - T / 2, rand() % T - T / 2, rand() % S - S));
            health->set_velocity(vec3(rand() % V - V / 2, rand() % V - V / 2, rand() % V - V / 2));
            // health->set_angular_velocity(vec3(rand() % A - A / 2, rand() % A - A / 2, rand() % A - A / 2));
        }
        else
        {
            Asteroid* asteroid = CodeMonkeys::TheGauntlet::GameObjects::AsteroidFactory::create_asteroid_random_size();
            this->world_root->add_child(asteroid);
            asteroid->set_position(vec3(rand() % T - T / 2, rand() % T - T / 2, rand() % S - S));
            asteroid->set_velocity(vec3(rand() % V - V / 2, rand() % V - V / 2, rand() % V - V / 2));
            asteroid->set_angular_velocity(vec3(rand() % A - A / 2, rand() % A - A / 2, rand() % A - A / 2));
        }
    }

    ship->set_position(vec3(0,0, S));

    auto checker = new BoundaryChecker(vec3(T, T, 0), vec3(-T, -T, -S - 20));
    this->set_boundary_checker(checker);

    this->set_collision_detector(new GridCollisionDetector(vec3(T, T, 0), vec3(-T, -T, -S), 100)); // this->set_collision_detector(new SimpleCollisionDetector());

    // Draw Portal
    auto portal = CodeMonkeys::TheGauntlet::GameObjects::PortalFactory::create_portal(ship);
    portal->set_position(vec3(0, 0, -S));
    this->world_root->add_child(portal);
}

void TheGauntletEngine::register_game_events()
{
    EventDispatcher::get_instance().register_event("next_level",
                                                   [this] ()
                                                   {
                                                       if (game_over)
                                                           return;

                                                       this->quads.clear();

                                                       Text* text = new Text("you win!", vec2(-0.77f, -0.2f), 0.4f);
                                                       text->set_character_spacing(0.4f);
                                                       text->set_line_spacing(0.8f);
                                                       this->quads.insert(text);

                                                       auto score_display = new ScoreDisplay(this, "score:", vec2(-0.65, -0.40f), 0.25);
                                                       score_display->set_character_spacing(0.5f);
                                                       this->quads.insert(score_display);

                                                       ship->hide_ship();
                                                       this->game_over = true;
                                                   }
    );

    EventDispatcher::get_instance().register_event("player_died",
                                                   [this] ()
                                                   {
                                                       if (game_over)
                                                           return;

                                                       this->quads.clear();

                                                       Text* text = new Text("you lose", vec2(-0.77f, -0.2f), 0.4f);
                                                       text->set_character_spacing(0.4f);
                                                       text->set_line_spacing(0.8f);
                                                       this->quads.insert(text);

                                                       auto score_display = new ScoreDisplay(this, "score:", vec2(-0.65, -0.40f), 0.25);
                                                       score_display->set_character_spacing(0.5f);
                                                       this->quads.insert(score_display);

                                                       ship->hide_ship();
                                                       this->game_over = true;
                                                   }
    );
}