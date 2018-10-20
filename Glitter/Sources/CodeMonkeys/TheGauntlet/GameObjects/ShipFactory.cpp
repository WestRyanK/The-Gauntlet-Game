#include "CodeMonkeys/TheGauntlet/GameObjects/ShipFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/Engine/Assets/Model3D.h"
#include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/Engine/Assets/ColorMaterial.h"
#include "CodeMonkeys/TheGauntlet/LaserCannon.h"
#include "CodeMonkeys/TheGauntlet/LaserTurret.h"
#include "CodeMonkeys/TheGauntlet/IFireable.h"
#include <vector>

using CodeMonkeys::TheGauntlet::GameObjects::ShipFactory;
using namespace CodeMonkeys::TheGauntlet::GameObjects; 
using namespace CodeMonkeys::TheGauntlet; 
using namespace CodeMonkeys::Engine::Assets;

vector<Material*> ShipFactory::ship_materials = vector<Material*>();

void ShipFactory::init(ShaderProgram* shader)
{
    Material* ship_material = new ColorMaterial(shader, true, 10.0f, vec3(8.0f), vec3(6.0f));
    vector<Material*> materials;
    materials.push_back(ship_material);
    ShipFactory::ship_materials = materials;
}

Ship* ShipFactory::create_x_wing_ship()
{
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Ships/XWingShip", "XWingShip.obj", *ml_model);


    Model3D* model = new Model3D(ml_model, ShipFactory::ship_materials);

    const unsigned int INTITIAL_HEALTH = 100;
    const unsigned int MAX_HEALTH =100;
    const float XY_ACCELERATION = 2;
    const float BOOST_ACCELERATION = 4;
    const float BRAKE_ACCELERATION = 2;
    const float MAX_XY_VELOCITY = 10;
    const float MAX_Z_VELOCITY = 15;
    const float MIN_Z_VELOCITY = 2;

    IFireable* laser_turret = new LaserTurret();
    IFireable* laser_cannon = new LaserCannon();

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

    return ship;
}