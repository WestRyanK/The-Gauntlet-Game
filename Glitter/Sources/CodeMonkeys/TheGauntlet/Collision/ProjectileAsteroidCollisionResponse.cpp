#include "CodeMonkeys/TheGauntlet/Collision/ProjectileAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/TheGauntlet/Projectile.h"
#include "CodeMonkeys/Engine/Engine/GameEngine.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/Engine/Objects/BillboardParticle.h"

using CodeMonkeys::TheGauntlet::Collision::ProjectileAsteroidCollisionResponse;
using namespace glm;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::Engine::Objects;

ProjectileAsteroidCollisionResponse::ProjectileAsteroidCollisionResponse(CodeMonkeys::Engine::Engine::GameEngine* engine) : ICollisionResponse(engine) 
{
    this->projectile_impact_emitter = new ParticleEmitter("projectile_impact_emitter");
    this->engine->get_world_root()->add_child(this->projectile_impact_emitter);

    AnimatedTexture* explosion_animation = new AnimatedTexture("Assets/Textures/Explosions/explosion_03/explosion", "png", 64);
    Billboard* explosion_billboard = new Billboard("projectile_impact_billboard", explosion_animation, 80, 80);
    BillboardParticle* explosion_particle = new BillboardParticle(explosion_billboard, "projectile_impact_particle", 1, this->projectile_impact_emitter);
    projectile_impact_emitter->set_particle(explosion_particle);
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

    if (asteroid != NULL && projectile->get_parent() != NULL && asteroid->get_parent() != NULL)
    {
        projectile->inflict_damage(asteroid);
        this->projectile_impact_emitter->set_position(asteroid->get_position() - glm::normalize(projectile->get_velocity()) * asteroid->get_size());
        projectile->get_parent()->remove_child(projectile);
        // asteroid->get_parent()->remove_child(asteroid);
        this->projectile_impact_emitter->emit(dt);
    }
}