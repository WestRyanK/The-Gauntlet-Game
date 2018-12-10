#include "CodeMonkeys/TheGauntlet/GameObjects/Asteroid.h"
#include <string>
#include <stdlib.h>
#include "CodeMonkeys/TheGauntlet/GameObjects/AsteroidFactory.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/Engine/Objects/Particle.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IInflicter.h"
#include "NIE.h"

using namespace std;
using CodeMonkeys::TheGauntlet::GameObjects::Asteroid;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::TheGauntlet::Weapons;

ParticleEmitter* Asteroid::asteroid_death_emitter = NULL;
Billboard* Asteroid::asteroid_death_billboard = NULL;
sf::SoundBuffer* Asteroid::sound_buffer = NULL;
sf::Sound* Asteroid::sound = NULL;

float Asteroid::LARGE_POINTS = 50.0f;
float Asteroid::MEDIUM_POINTS = 30.0f;
float Asteroid::SMALL_POINTS = 10.0f;

Asteroid::Asteroid(Model3D* model, unsigned int size_class, unsigned int health, float size, unsigned int inflict_amount, float points, IScoreKeeper* score_keeper) : PhysicalObject3D(model, "asteroid"), IDamageable(health, health), IInflicter(inflict_amount)
{
    this->size_class = size_class;
    this->size = size;
    this->score_keeper = score_keeper;
    this->points = points;
    // TODO: Adjust size
    this->bounding_sphere = new BoundingSphere(this->position, size);
}

void Asteroid::init(Object3D* world_root)
{
    Asteroid::asteroid_death_emitter = new ParticleEmitter("asteroid_death_emitter");
    world_root->add_child(Asteroid::asteroid_death_emitter);

    AnimatedTexture* asteroid_death_animation = new AnimatedTexture("Assets/Explosions/Explosion_02/explosion", "png", 64);
    Asteroid::asteroid_death_billboard = new Billboard("projectile_impact_billboard", asteroid_death_animation, 120, 120);
    Particle* asteroid_death_particle = new Particle(NULL, asteroid_death_billboard, "asteroid_death_particle", 1.5, Asteroid::asteroid_death_emitter);
    Asteroid::asteroid_death_emitter->set_particle(asteroid_death_particle);

    Asteroid::sound = new sf::Sound();
    Asteroid::sound_buffer = new sf::SoundBuffer();
    if (!Asteroid::sound_buffer->loadFromFile("Assets/Explosions/Explosion_02/explosion_02.wav"))
        printf("Could not load 'explosion_02.wav' file!\n");
    Asteroid::sound->setBuffer(*Asteroid::sound_buffer);
    Asteroid::sound->setVolume(100.0f);
}

void Asteroid::update(float dt)
{
    PhysicalObject3D::update(dt);
    this->bounding_sphere->set_center(this->position);
}

ICollisionRegion* Asteroid::get_collision_region()
{
    return this->bounding_sphere;
}

unsigned int Asteroid::get_size_class()
{
    return this->size_class;
}

float Asteroid::get_size()
{
    return this->size;
}

void Asteroid::on_death()
{
    Asteroid::sound->play();

    if (this->size_class > 1)
    {
        const int MAX_VELOCITY = 20;
        for (int i = 0; i < 3; i++)
        {
            Asteroid* asteroid = AsteroidFactory::create_asteroid(this->size_class - 1);
            asteroid->set_position(this->get_position());
            asteroid->set_velocity(vec3(rand() % MAX_VELOCITY - MAX_VELOCITY / 2, rand() % MAX_VELOCITY - MAX_VELOCITY / 2, rand() % MAX_VELOCITY - MAX_VELOCITY / 2));
            this->get_parent()->add_child(asteroid);
        }
    }
    else
    {
    }
    this->score_keeper->add_points(this->points);

    Asteroid::asteroid_death_billboard->set_height(this->size * 20);
    Asteroid::asteroid_death_billboard->set_width(this->size * 20);
    Asteroid::asteroid_death_emitter->emit(1.0f);
    Asteroid::asteroid_death_emitter->set_position(this->get_position());
    this->get_parent()->remove_child(this);
}

float Asteroid::get_points()
{
    return this->points;
}