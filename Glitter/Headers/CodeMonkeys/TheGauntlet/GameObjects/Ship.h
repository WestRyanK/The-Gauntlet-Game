#pragma once

#include <string>
#include "glitter.hpp"
#include "CodeMonkeys/TheGauntlet/IFireable.h"
#include "CodeMonkeys/TheGauntlet/IFlyable.h"
#include "CodeMonkeys/TheGauntlet/IDamageable.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Assets/Model3D.h"

using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::Control;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Ship : public PhysicalObject3D, public IDamageable, public IControllable, public IFlyable
    {
    protected:
        IFireable* primary_weapon = NULL;
        IFireable* secondary_weapon = NULL;

        void on_death();
        void control(std::string control_name, float value, float dt);
        void control(std::string control_name, int value, float dt);

    public:
        Ship(Model3D* model, std::string name,
            unsigned int initial_health,
            unsigned int max_health, 
            float xy_acceleration, 
            float boost_acceleration,
            float brake_acceleration,
            float max_xy_velocity,
            float max_z_velocity,
            float min_z_velocity,
            IFireable* primary_weapon,
            IFireable* secondary_weapon);
    };
}