#pragma once

#include <string>
#include "glitter.hpp"
#include "CodeMonkeys/TheGauntlet/Weapons/Weapon.h"
#include "CodeMonkeys/TheGauntlet/IFlyable.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IDamageable.h"
#include "CodeMonkeys/Engine/Control/IControllable.h"
#include "CodeMonkeys/Engine/Objects/PhysicalObject3D.h"
#include "CodeMonkeys/Engine/Assets/Model3D.h"
#include "CodeMonkeys/Engine/Collision/BoundingMultiSphere.h"

using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::Control;
using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::TheGauntlet::Weapons;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class Ship : public PhysicalObject3D, public IDamageable, public IControllable, public IFlyable
    {
    protected:
        Weapon* primary_weapon = NULL;
        Weapon* secondary_weapon = NULL;

        void on_death();
        void control(std::string control_name, float value, float dt);
        void control(std::string control_name, int value, float dt);
        void update(float dt);
        void update_vertical(float dt);
        void update_lateral(float dt);
        void dampen_lateral(float dt);
        void dampen_vertical(float dt);
        bool acclerating_vertically;
        bool acclerating_laterally;
        BoundingMultiSphere* bounding_multisphere;

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
            Weapon* primary_weapon,
            Weapon* secondary_weapon);

        ICollisionRegion* get_collision_region();
        Weapon* get_primary_weapon();
        Weapon* get_secondary_weapon();
    };
}
