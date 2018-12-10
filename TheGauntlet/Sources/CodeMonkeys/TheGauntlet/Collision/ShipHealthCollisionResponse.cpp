#include "CodeMonkeys/TheGauntlet/Collision/ShipHealthCollisionResponse.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Health.h"
#include "CodeMonkeys/Engine/Engine/GameEngine.h"

using CodeMonkeys::TheGauntlet::Collision::ShipHealthCollisionResponse;
using namespace glm;
using namespace CodeMonkeys::TheGauntlet::GameObjects;
using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::Engine::Objects;

ShipHealthCollisionResponse::ShipHealthCollisionResponse(CodeMonkeys::Engine::Engine::GameEngine* engine, IScoreKeeper* score_keeper) : ICollisionResponse(engine) 
{
    this->score_keeper = score_keeper;

    this->sound_buffer = new sf::SoundBuffer();
    if (!this->sound_buffer->loadFromFile("Assets/Health/heal.wav"))
        printf("Could not load 'heal' file!\n");
    this->sound = new sf::Sound();
    this->sound->setVolume(50.0f);
    this->sound->setBuffer(*this->sound_buffer);
}

bool ShipHealthCollisionResponse::can_respond(Object3D* object_a, Object3D* object_b)
{
    Ship* ship = dynamic_cast<Ship*> (object_a);
    Health* health = dynamic_cast<Health*> (object_b);

    Ship* ship2 = dynamic_cast<Ship*> (object_b);
    Health* health2 = dynamic_cast<Health*> (object_a);

    return (ship != NULL && health != NULL) || (ship2 != NULL && health2 != NULL);
}

void ShipHealthCollisionResponse::respond(Object3D* object_a, Object3D* object_b, float dt)
{
    Ship* ship = dynamic_cast<Ship*> (object_a);
    Health* health = dynamic_cast<Health*> (object_b);
    if (ship == NULL && health == NULL)
    {
        swap(object_a, object_b);
        ship = dynamic_cast<Ship*> (object_a);
        health = dynamic_cast<Health*> (object_b);
    }

    if (ship != NULL && health != NULL && ship->get_parent() != NULL && health->get_parent() != NULL)
    {
        this->sound->play();

        ship->heal_health(health->get_inflict_amount());
        health->get_parent()->remove_child(health);
        score_keeper->add_points(35);
    }
}