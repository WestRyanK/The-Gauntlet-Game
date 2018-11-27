#include "CodeMonkeys/TheGauntlet/Collision/ShipAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/Engine/Engine/GameEngine.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"

using CodeMonkeys::TheGauntlet::Collision::ShipAsteroidCollisionResponse;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::Engine::Objects;

ShipAsteroidCollisionResponse::ShipAsteroidCollisionResponse(CodeMonkeys::Engine::Engine::GameEngine* engine) : ICollisionResponse(engine) 
{
}

bool ShipAsteroidCollisionResponse::can_respond(Object3D* object_a, Object3D* object_b)
{
    Ship* ship = dynamic_cast<Ship*> (object_a);
    Asteroid* asteroid = dynamic_cast<Asteroid*> (object_b);

    Ship* ship2 = dynamic_cast<Ship*> (object_b);
    Asteroid* asteroid2 = dynamic_cast<Asteroid*> (object_a);

    return (ship != NULL && asteroid != NULL) || (ship2 != NULL && asteroid2 != NULL);
}

void ShipAsteroidCollisionResponse::respond(Object3D* object_a, Object3D* object_b, float dt)
{
    Ship* ship = dynamic_cast<Ship*> (object_a);
    Asteroid* asteroid = dynamic_cast<Asteroid*> (object_b);
    if (ship == NULL && asteroid == NULL)
        swap(object_a, object_b);

    if (object_b != NULL && object_b->get_parent() != NULL)
    {
        object_b->get_parent()->remove_child(object_b);
        ParticleEmitter* emitter = NULL;
        for (Object3D* child : object_a->get_children())
        {
            if (child->get_name() == "ship_explosion_emitter")
            {
                emitter = dynamic_cast<ParticleEmitter*> (child);
            }
        }
        emitter->emit(dt);
    }
}