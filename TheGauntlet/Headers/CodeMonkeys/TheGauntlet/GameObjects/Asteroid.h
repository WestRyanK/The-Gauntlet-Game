#pragma once

#include <SFML/Audio.hpp>
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IDamageable.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IInflicter.h"
#include "CodeMonkeys/Engine/Collision/BoundingSphere.h"
#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/TheGauntlet/IScoreKeeper.h"

using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::TheGauntlet::Weapons;
using namespace CodeMonkeys::TheGauntlet;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Asteroid : public PhysicalObject3D, public IDamageable, public IInflicter
    {
    private:
        unsigned int size_class;
        float size;
        float points;
        IScoreKeeper* score_keeper;
        BoundingSphere* bounding_sphere;
        void on_death();
        static ParticleEmitter* asteroid_death_emitter;
        static Billboard* asteroid_death_billboard;
        static sf::SoundBuffer* sound_buffer;
        static sf::Sound* sound;

    public:
        Asteroid(Model3D* model, unsigned int size_class, unsigned int health, float size, unsigned int inflict_amount, float points, IScoreKeeper* score_keeper);
        static void init(Object3D* world_root);
        unsigned int get_size_class();
        float get_size();
        unsigned int get_health();
        virtual void update(float dt);
        float get_points();
        ICollisionRegion* get_collision_region();
        static const unsigned int LARGE = 3;
        static const unsigned int MEDIUM = 2;
        static const unsigned int SMALL = 1;

        static const unsigned int LARGE_HEALTH = 5;
        static const unsigned int MEDIUM_HEALTH = 3;
        static const unsigned int SMALL_HEALTH = 1;

        static const unsigned int LARGE_INFLICT = 35;
        static const unsigned int MEDIUM_INFLICT = 25;
        static const unsigned int SMALL_INFLICT = 15;

        static float LARGE_POINTS;
        static float MEDIUM_POINTS;
        static float SMALL_POINTS;
    };
}