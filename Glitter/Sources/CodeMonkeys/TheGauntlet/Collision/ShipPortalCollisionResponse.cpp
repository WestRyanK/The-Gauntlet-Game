#include "CodeMonkeys/TheGauntlet/Collision/ShipPortalCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Portal.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "glitter.hpp"

using CodeMonkeys::TheGauntlet::Collision::ShipPortalCollisionResponse;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

ShipPortalCollisionResponse::ShipPortalCollisionResponse(CodeMonkeys::Engine::Engine::GameEngine* engine) : ICollisionResponse(engine)
{
}

bool ShipPortalCollisionResponse::can_respond(Object3D* object_a, Object3D* object_b)
{
    auto portal1 = dynamic_cast<Portal*> (object_a);
    auto ship1 = dynamic_cast<Ship*> (object_b);

    auto portal2 = dynamic_cast<Portal*> (object_b);
    auto ship2 = dynamic_cast<Ship*> (object_a);

    return (portal1 != NULL && ship1 != NULL || portal2 != NULL && ship2 != NULL);
}

void ShipPortalCollisionResponse::respond(Object3D* object_a, Object3D* object_b, float dt)
{
    if (can_respond(object_a, object_b))
    {
        Portal* portal;
        Ship* ship;

        if (dynamic_cast<Portal*> (object_a) != NULL)
        {
            portal = dynamic_cast<Portal*> (object_a);
            ship = dynamic_cast<Ship*> (object_b);
        }
        else
        {
            portal = dynamic_cast<Portal*> (object_b);
            ship = dynamic_cast<Ship*> (object_a);
        }

        printf("inside\n");
        if (ship->get_transformed_position().z <= portal->get_transformed_position().z)
        {
            printf("You Win!\n");
            exit(0);
        }
    }
}
