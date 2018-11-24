#include "CodeMonkeys/TheGauntlet/Collision/ShipAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/Engine/Engine/GameEngine.h"

using CodeMonkeys::TheGauntlet::Collision::ShipAsteroidCollisionResponse;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::Engine::Engine;

ShipAsteroidCollisionResponse::ShipAsteroidCollisionResponse(CodeMonkeys::Engine::Engine::GameEngine* engine) : ICollisionResponse(engine) 
{
    this->explosion_animation = new AnimatedTexture("Assets/Textures/Explosions/explosion_01/explosion", "png", 64);
}

bool ShipAsteroidCollisionResponse::can_respond(Object3D* object_a, Object3D* object_b)
{
    Ship* ship = dynamic_cast<Ship*> (object_a);
    Asteroid* asteroid = dynamic_cast<Asteroid*> (object_b);

    return (ship != NULL && asteroid != NULL);
}

void ShipAsteroidCollisionResponse::respond(Object3D* object_a, Object3D* object_b, float dt)
{
    printf("BOOOM!!!");
    Billboard* explosion = new Billboard("explosion", this->explosion_animation, 40, 40);
    explosion->set_position(object_a->get_position());
    this->engine->get_world_root()->add_child(explosion);
}