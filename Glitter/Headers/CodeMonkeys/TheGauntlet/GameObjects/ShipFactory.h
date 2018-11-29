#pragma once

#include <vector>
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
#include "CodeMonkeys/Engine/Objects/ParticleEmitter.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"

using namespace std;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class ShipFactory
    {
    private:
        static ParticleEmitter* projectile_emitter;
        static vector<Material*> ship_materials;
    public:
        static Ship* create_x_wing_ship();
        static void init(ShaderProgram* shader, ParticleEmitter* projectile_emitter);
    };
}