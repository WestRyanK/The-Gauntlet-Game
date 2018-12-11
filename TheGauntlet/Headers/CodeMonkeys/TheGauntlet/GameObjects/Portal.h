#pragma once

#include <SFML/Audio.hpp>
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"

using namespace CodeMonkeys::Engine::Objects;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Portal : public PhysicalObject3D
    {
    private:
        sf::Sound* sound;
        sf::SoundBuffer* sound_buffer;
        Ship* ship;
        BoundingSphere* bounding_sphere;
    public:
        Portal(Model3D* model, Ship* ship);
        ICollisionRegion* get_collision_region();
        void update(float dt);
    };
}