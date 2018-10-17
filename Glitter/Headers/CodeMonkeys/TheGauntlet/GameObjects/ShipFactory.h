#pragma once

#include <vector>
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"

using namespace std;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class ShipFactory
    {
    private:
        static vector<Material*> ship_materials;
    public:
        static Ship* create_x_wing_ship();
        static void init(ShaderProgram* shader);
    };
}