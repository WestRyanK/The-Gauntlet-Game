#include "CodeMonkeys/TheGauntlet/GameObjects/ShipFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/Engine/Assets/Model3D.h"
#include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/Engine/Objects/BillboardParticle.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/TheGauntlet/LaserCannon.h"
#include "CodeMonkeys/TheGauntlet/LaserTurret.h"
#include "CodeMonkeys/TheGauntlet/Weapon.h"
#include <vector>

using CodeMonkeys::TheGauntlet::GameObjects::ShipFactory;
using namespace CodeMonkeys::TheGauntlet::GameObjects; 
using namespace CodeMonkeys::TheGauntlet; 
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::Engine::Objects;

ParticleEmitter* ShipFactory::projectile_emitter = NULL;
vector<Material*> ShipFactory::ship_materials = vector<Material*>();

void ShipFactory::init(ShaderProgram* shader, ParticleEmitter* projectile_emitter)
{
    Material* ship_material = new ColorMaterial(shader, true, 10.0f, vec3(0.8f), vec3(0.9f, 0.9f, 0.9f));
    vector<Material*> materials;
    materials.push_back(ship_material);
    ShipFactory::ship_materials = materials;
    ShipFactory::projectile_emitter = projectile_emitter;
}

Ship* ShipFactory::create_x_wing_ship()
{
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Ships/XWingShip", "XWingShip.obj", *ml_model);


    Model3D* model = new Model3D(ml_model, ShipFactory::ship_materials);

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

    Weapon* laser_turret = new LaserTurret(ship_materials[0]->get_shader(), ShipFactory::projectile_emitter);
    Weapon* laser_cannon = new LaserCannon(ship_materials[0]->get_shader(), ShipFactory::projectile_emitter);

    Ship* ship = new Ship(model, "x_wing_ship",
                          INTITIAL_HEALTH, MAX_HEALTH,
                          XY_ACCELERATION,
                          BOOST_ACCELERATION,
                          BRAKE_ACCELERATION,
                          MAX_XY_VELOCITY,
                          MAX_Z_VELOCITY,
                          MIN_Z_VELOCITY,
                          laser_turret,
                          laser_cannon);

    ParticleEmitter* ship_explosion_emitter = new ParticleEmitter("ship_explosion_emitter"); // This name is important! Used in ShipAsteroidCollisionResponse
    ship_explosion_emitter->set_position(vec3(0, 0, 15));
    ship->add_child(ship_explosion_emitter);

    AnimatedTexture* explosion_animation = new AnimatedTexture("Assets/Textures/Explosions/explosion_01/explosion", "png", 64);
    Billboard* explosion_billboard = new Billboard("billboard_explosion", explosion_animation, 80, 80);
    BillboardParticle* explosion_particle = new BillboardParticle(explosion_billboard, "explosion_particle", 1, ship_explosion_emitter);
    ship_explosion_emitter->set_particle(explosion_particle);

    return ship;
}