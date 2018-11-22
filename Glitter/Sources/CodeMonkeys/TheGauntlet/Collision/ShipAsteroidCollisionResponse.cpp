#include "CodeMonkeys/TheGauntlet/Collision/ShipAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"

using CodeMonkeys::TheGauntlet::Collision::ShipAsteroidCollisionResponse;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

bool ShipAsteroidCollisionResponse::can_respond(Object3D* object_a, Object3D* object_b)
{
    Ship* ship = dynamic_cast<Ship*> (object_a);
    Asteroid* asteroid = dynamic_cast<Asteroid*> (object_b);

    return (ship != NULL && asteroid != NULL);
}

void ShipAsteroidCollisionResponse::respond(Object3D* object_a, Object3D* object_b, float dt)
{
    printf("BOOOM!!!");
}