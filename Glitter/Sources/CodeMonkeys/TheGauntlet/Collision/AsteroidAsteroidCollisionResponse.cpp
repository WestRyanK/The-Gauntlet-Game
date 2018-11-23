#include "CodeMonkeys/TheGauntlet/Collision/AsteroidAsteroidCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include "glitter.hpp"

using CodeMonkeys::TheGauntlet::Collision::AsteroidAsteroidCollisionResponse;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

bool AsteroidAsteroidCollisionResponse::can_respond(Object3D* object_a, Object3D* object_b)
{
    Asteroid* asteroid_a = dynamic_cast<Asteroid*> (object_a);
    Asteroid* asteroid_b = dynamic_cast<Asteroid*> (object_b);

    return (asteroid_a != NULL && asteroid_b != NULL);
}

void AsteroidAsteroidCollisionResponse::respond(Object3D* object_a, Object3D* object_b, float dt)
{
    Asteroid* asteroid_a = (Asteroid*)object_a;
    Asteroid* asteroid_b = (Asteroid*)object_b;

    float speed_a = glm::length(asteroid_a->get_velocity());
    float speed_b = glm::length(asteroid_b->get_velocity());
    
    // Reflect the asteroids' trajectory using the normal between their surfaces.
    // Since they are spheres, we assume the normal to be simply the difference between positions.
    vec3 hit_normal = glm::normalize(asteroid_a->get_position() - asteroid_b->get_position());
    vec3 new_direction_a = normalize(2.0f * hit_normal * dot(-hit_normal, asteroid_a->get_velocity()) + asteroid_a->get_velocity());
    vec3 new_direction_b = normalize(2.0f * hit_normal * dot(-hit_normal, asteroid_b->get_velocity()) + asteroid_b->get_velocity());

    // To keep the asteroids from colliding multiple times, we rewind time a few frames
    // by moving them back in the direction they came from.
    const float REWIND_FRAMES = 1.25f;
    asteroid_a->set_position(asteroid_a->get_position() + hit_normal * speed_a * dt * REWIND_FRAMES);
    asteroid_b->set_position(asteroid_b->get_position() - hit_normal * speed_b * dt * REWIND_FRAMES);

    // TODO: Use Elastic collision equations!
    asteroid_a->set_velocity(new_direction_a * speed_a);
    asteroid_b->set_velocity(new_direction_b * speed_b);
}