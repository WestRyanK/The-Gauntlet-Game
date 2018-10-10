#include "CodeMonkeys/TheGauntlet/GameObjects/ShipFactory.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/Engine/Assets/Model3D.h"
#include "CodeMonkeys/Engine/Assets/ModelLoader.h"
#include "CodeMonkeys/Engine/Assets/ShaderHelpers.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"
#include "CodeMonkeys/TheGauntlet/LaserCannon.h"
#include "CodeMonkeys/TheGauntlet/LaserTurret.h"
#include "CodeMonkeys/TheGauntlet/IFireable.h"
#include <vector>

using CodeMonkeys::TheGauntlet::GameObjects::ShipFactory;
using namespace CodeMonkeys::TheGauntlet::GameObjects; 
using namespace CodeMonkeys::TheGauntlet; 
using namespace CodeMonkeys::Engine::Assets;

vector<ShaderProgram> ShipFactory::ship_shaders = vector<ShaderProgram>();
vector<Texture*> ShipFactory::ship_textures = vector<Texture*>();

void ShipFactory::init(vector<ShaderProgram> ship_shaders, vector<Texture*> ship_textures)
{
    ShipFactory::ship_shaders = ship_shaders;
    ShipFactory::ship_textures = ship_textures;
}

Ship* ShipFactory::create_x_wing_ship()
{
    mlModel* ml_model = new mlModel();
    LoadModel("Assets/Ships/XWingShip", "XWingShip.obj", *ml_model);


    Model3D* model = new Model3D(ml_model, ShipFactory::ship_textures, ShipFactory::ship_shaders);

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