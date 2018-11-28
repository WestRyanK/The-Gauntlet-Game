#include "CodeMonkeys/TheGauntlet/Collision/ProjectileAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/TheGauntlet/Projectile.h"
#include "CodeMonkeys/Engine/Engine/GameEngine.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"

using CodeMonkeys::TheGauntlet::Collision::ProjectileAsteroidCollisionResponse;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::Engine::Objects;

ProjectileAsteroidCollisionResponse::ProjectileAsteroidCollisionResponse(CodeMonkeys::Engine::Engine::GameEngine* engine) : ICollisionResponse(engine) 
{
}

bool ProjectileAsteroidCollisionResponse::can_respond(Object3D* object_a, Object3D* object_b)
{
    Projectile* projectile = dynamic_cast<Projectile*> (object_a);
    Asteroid* asteroid = dynamic_cast<Asteroid*> (object_b);

    Projectile* projectile2 = dynamic_cast<Projectile*> (object_b);
    Asteroid* asteroid2 = dynamic_cast<Asteroid*> (object_a);

    return (projectile != NULL && asteroid != NULL) || (projectile2 != NULL && asteroid2 != NULL);
}

void ProjectileAsteroidCollisionResponse::respond(Object3D* object_a, Object3D* object_b, float dt)
{
    Projectile* projectile = dynamic_cast<Projectile*> (object_a);
    Asteroid* asteroid = dynamic_cast<Asteroid*> (object_b);
    if (projectile == NULL && asteroid == NULL)
    {
        swap(object_a, object_b);
        projectile = dynamic_cast<Projectile*> (object_a);
        asteroid = dynamic_cast<Asteroid*> (object_b);
    }

    if (asteroid != NULL && projectile->get_parent() != NULL)
    {
        asteroid->inflict_damage(projectile->get_inflict_amount());
        projectile->get_parent()->remove_child(projectile);
        asteroid->get_parent()->remove_child(asteroid);
        ParticleEmitter* emitter = NULL;
        for (Object3D* child : object_a->get_children())
        {
            if (child->get_name() == "ship_explosion_emitter")
            {
                emitter = dynamic_cast<ParticleEmitter*> (child);
            }
        }
        if (emitter != NULL)
            emitter->emit(dt);
    }
}