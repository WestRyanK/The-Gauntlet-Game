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
        static ShaderProgram* projectile_shader;
        static ShaderProgram* ship_shader;
        static void add_explosion_particles(Ship* ship);
    public:
        static Ship* create_x_wing_ship();
        static Ship* create_jet_fighter();
        static Ship* create_crayon_ship();
        static void init(ShaderProgram* shader, ParticleEmitter* projectile_emitter, ShaderProgram* projectile_shader);
    };
}