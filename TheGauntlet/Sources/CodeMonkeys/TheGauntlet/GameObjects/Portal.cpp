#include "CodeMonkeys/TheGauntlet/GameObjects/Portal.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"
#include <string>
#include <Portal.h>
#include "NIE.h"
#include <glitter.hpp>

using namespace glm;
using CodeMonkeys::TheGauntlet::GameObjects::Portal;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::GameObjects;

Portal::Portal(Model3D* model, Ship* ship) : PhysicalObject3D(model, "portal")
{
    this->sound = new sf::Sound();
    this->sound_buffer = new sf::SoundBuffer();
    if (!this->sound_buffer->loadFromFile("Assets/Portal/portal.wav"))
        printf("Could not load 'portal.wav' file!\n");
    this->sound->setVolume(0);
    this->sound->setBuffer(*this->sound_buffer);
    this->sound->play();


    this->bounding_sphere = new BoundingSphere(this->position, 40);
    this->set_scale(1.0f);

    this->ship = ship;
}

ICollisionRegion* Portal::get_collision_region()
{
    return this->bounding_sphere;
}

void Portal::update(float dt)
{
    float MAX_DISTANCE_HEARD = 2000;
    float distance_between_ship_and_portal = glm::length(this->get_transformed_position() - this->ship->get_transformed_position());
    float volume = 100 * sqrt((MAX_DISTANCE_HEARD - distance_between_ship_and_portal) / MAX_DISTANCE_HEARD);
    volume = std::max((float)0.0f, (float)volume);
    volume = std::min((float)100.0f, (float)volume);
    this->sound->setVolume( volume);
    PhysicalObject3D::update(dt);
    this->bounding_sphere->set_center(this->position);
}