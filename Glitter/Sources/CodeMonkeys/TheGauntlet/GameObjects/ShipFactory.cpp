#include "CodeMonkeys/TheGauntlet/GameObjects/ShipFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/Engine/Assets/Model3D.h"
#include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Assets/TextureMaterial.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/TheGauntlet/Weapons/LaserCannon.h"
#include "CodeMonkeys/TheGauntlet/Weapons/AntiMatterCannon.h"
#include "CodeMonkeys/TheGauntlet/Weapons/LaserTurret.h"
#include "CodeMonkeys/TheGauntlet/Weapons/BeamGun.h"
#include "CodeMonkeys/TheGauntlet/Weapons/CrayonLauncher.h"
#include "CodeMonkeys/TheGauntlet/Weapons/Weapon.h"
#include <vector>

using CodeMonkeys::TheGauntlet::GameObjects::ShipFactory;
using namespace CodeMonkeys::TheGauntlet::GameObjects; 
using namespace CodeMonkeys::TheGauntlet; 
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::Weapons;


ParticleEmitter* ShipFactory::projectile_emitter = NULL;
ShaderProgram* ShipFactory::projectile_shader = NULL;
ShaderProgram* ShipFactory::ship_shader = NULL;

void ShipFactory::init(ShaderProgram* shader, ParticleEmitter* projectile_emitter, ShaderProgram* projectile_shader)
{
    ShipFactory::projectile_emitter = projectile_emitter;
    ShipFactory::projectile_shader = projectile_shader;
    ShipFactory::ship_shader = shader;
}

Ship* ShipFactory::create_crayon_ship()
{
    Texture* texture = new Texture("Assets/Ships/CrayonBox/box_texture.png");
    Material* ship_material = new TextureMaterial(ShipFactory::ship_shader, true, 10.0f, vec3(0.8f), vec3(1), texture);
    vector<Material*> materials;
    materials.push_back(ship_material);

    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Ships/CrayonBox", "box.obj", *ml_model);

    Model3D* model = new Model3D(ml_model, materials);

    const unsigned int INTITIAL_HEALTH = 50;
    const unsigned int MAX_HEALTH =50;
    const float XY_ACCELERATION = 50;
    const float BOOST_ACCELERATION = 10;
    const float BRAKE_ACCELERATION = 2;
    const float MAX_XY_VELOCITY = 10;
    const float MAX_Z_VELOCITY = 0;
    const float MIN_Z_VELOCITY = 0;

    Weapon* crayon_launcher = new CrayonLauncher(ShipFactory::ship_shader, ShipFactory::projectile_emitter);

    auto crosshairs = new Crosshairs(new Texture("Assets/Ships/XWingShip/crosshairs.png"));

    Ship* ship = new Ship(model, "ship",
                          INTITIAL_HEALTH, MAX_HEALTH,
                          XY_ACCELERATION,
                          BOOST_ACCELERATION,
                          BRAKE_ACCELERATION,
                          MAX_XY_VELOCITY,
                          MAX_Z_VELOCITY,
                          MIN_Z_VELOCITY,
                          crayon_launcher,
                          NULL,
                          NULL,
                          crosshairs);

    ShipFactory::add_explosion_particles(ship);
    ship->add_child(crosshairs);

    return ship;
}

void ShipFactory::add_explosion_particles(Ship* ship)
{
    ParticleEmitter* ship_explosion_emitter = new ParticleEmitter("ship_explosion_emitter"); // This name is important! Used in ShipAsteroidCollisionResponse
    ship_explosion_emitter->set_position(vec3(0, 0, 15));
    ship->add_child(ship_explosion_emitter);

    AnimatedTexture* explosion_animation = new AnimatedTexture("Assets/Explosions/Explosion_01/explosion", "png", 64);
    Billboard* explosion_billboard = new Billboard("billboard_explosion", explosion_animation, 80, 80);
    Particle* explosion_particle = new Particle(NULL, explosion_billboard, "explosion_particle", 1, ship_explosion_emitter);
    ship_explosion_emitter->set_particle(explosion_particle);
}

Ship* ShipFactory::create_x_wing_ship()
{
    Material* ship_material = new ColorMaterial(ShipFactory::ship_shader, true, 10.0f, vec3(0.8f), vec3(0.2f, 0.4f, 0.9f));
    vector<Material*> materials;
    materials.push_back(ship_material);

    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Ships/XWingShip", "x_wing_ship.obj", *ml_model);

    Model3D* model = new Model3D(ml_model, materials);

    const unsigned int INTITIAL_HEALTH = 100;
    const unsigned int MAX_HEALTH =100;
    const float XY_ACCELERATION = 50;
    const float BOOST_ACCELERATION = 10;
    const float BRAKE_ACCELERATION = 2;
    const float MAX_XY_VELOCITY = 10;
    const float MAX_Z_VELOCITY = 0;
    // const float MAX_Z_VELOCITY = 20;
    const float MIN_Z_VELOCITY = 0;
    // const float MIN_Z_VELOCITY = 5;


    Weapon* laser_turret = new LaserTurret(ShipFactory::projectile_shader, ShipFactory::projectile_emitter);
    laser_turret->set_position(vec3(3.7f,-2.4f,0));
    Weapon* laser_cannon = new LaserCannon(ShipFactory::projectile_shader, ShipFactory::projectile_emitter);

    AnimatedTexture* rocket_texture = new AnimatedTexture("Assets/Ships/XWingShip/rocket", "png", 8);
    RocketEngine* rocket_engine = new RocketEngine(rocket_texture, 16, 16, "Assets/Ships/XWingShip/engine.wav");
    rocket_engine->set_position(vec3(0, 0, 8.85f));

    rocket_engine->set_acceleration_volume(60);
    rocket_engine->set_deceleration_volume(30);
    rocket_engine->set_max_volume(45);
    rocket_engine->set_min_volume(20);

    rocket_engine->set_acceleration_pitch(1.0f);
    rocket_engine->set_deceleration_pitch(0.5f);
    rocket_engine->set_max_pitch(1.0f);
    rocket_engine->set_min_pitch(0.4f);

    rocket_engine->set_acceleration_frame(20);
    rocket_engine->set_deceleration_frame(7);
    rocket_engine->set_twitch_frame(true);

    auto crosshairs = new Crosshairs(new Texture("Assets/Ships/XWingShip/crosshairs.png"));

    Ship* ship = new Ship(model, "ship",
                          INTITIAL_HEALTH, MAX_HEALTH,
                          XY_ACCELERATION,
                          BOOST_ACCELERATION,
                          BRAKE_ACCELERATION,
                          MAX_XY_VELOCITY,
                          MAX_Z_VELOCITY,
                          MIN_Z_VELOCITY,
                          laser_turret,
                          laser_cannon,
                          rocket_engine,
                          crosshairs);

    ship->add_child(rocket_engine);
    ShipFactory::add_explosion_particles(ship);
    ship->add_child(crosshairs);

    return ship;
}

Ship* ShipFactory::create_jet_fighter()
{
    Material* ship_material = new ColorMaterial(ShipFactory::ship_shader, true, 10.0f, vec3(0.8f), vec3(0.2f, 0.4f, 0.9f));
    vector<Material*> materials;
    materials.push_back(ship_material);

    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Ships/JetFighter", "jet_fighter.obj", *ml_model);

    Model3D* model = new Model3D(ml_model, materials);

    const unsigned int INTITIAL_HEALTH = 125;
    const unsigned int MAX_HEALTH =125;
    const float XY_ACCELERATION = 50;
    const float BOOST_ACCELERATION = 10;
    const float BRAKE_ACCELERATION = 2;
    const float MAX_XY_VELOCITY = 10;
    const float MAX_Z_VELOCITY = 0;
    // const float MAX_Z_VELOCITY = 20;
    const float MIN_Z_VELOCITY = 0;
    // const float MIN_Z_VELOCITY = 5;

    Weapon* beam_gun = new BeamGun(ShipFactory::projectile_shader, ShipFactory::projectile_emitter);
    beam_gun->set_position(vec3(3,-1,0));
    Weapon* antimatter_cannon = new AntiMatterCannon(ShipFactory::projectile_shader, ShipFactory::projectile_emitter);

    auto rocket_texture = new AnimatedTexture("Assets/Ships/JetFighter/rocket", "png", 8);
    auto rocket_engine = new RocketEngine(rocket_texture, 12, 12, "Assets/Ships/JetFighter/engine.wav");
    rocket_engine->set_position(vec3(0,-1.6,12.4));
    rocket_engine->set_scale(rocket_engine->get_scale() * 1.2f);

    rocket_engine->set_acceleration_volume(80);
    rocket_engine->set_deceleration_volume(20);
    rocket_engine->set_max_volume(50);
    rocket_engine->set_min_volume(30);

    rocket_engine->set_acceleration_pitch(1.2f);
    rocket_engine->set_deceleration_pitch(0.3f);
    rocket_engine->set_max_pitch(1.1f);
    rocket_engine->set_min_pitch(0.4f);

    rocket_engine->set_acceleration_frame(20);
    rocket_engine->set_deceleration_frame(5);
    rocket_engine->set_twitch_frame(true);

    auto crosshairs = new Crosshairs(new Texture("Assets/Ships/JetFighter/crosshairs.png"));

    Ship* ship = new Ship(model, "ship",
                          INTITIAL_HEALTH, MAX_HEALTH,
                          XY_ACCELERATION,
                          BOOST_ACCELERATION,
                          BRAKE_ACCELERATION,
                          MAX_XY_VELOCITY,
                          MAX_Z_VELOCITY,
                          MIN_Z_VELOCITY,
                          beam_gun,
                          antimatter_cannon,
                          rocket_engine,
                          crosshairs);

    ship->add_child(rocket_engine);
    ship->add_child(crosshairs);
    ShipFactory::add_explosion_particles(ship);

    return ship;
}