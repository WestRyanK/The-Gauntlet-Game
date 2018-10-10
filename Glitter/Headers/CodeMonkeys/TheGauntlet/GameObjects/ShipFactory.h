#pragma once

#include "CodeMonkeys/Engine/Assets/Texture.h"
#include <vector>
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"

using namespace std;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class ShipFactory
    {
    private:
        static vector<ShaderProgram> ship_shaders;
        static vector<Texture*> ship_textures;
    public:
        static Ship* create_x_wing_ship();
        static void init(vector<ShaderProgram> ship_shaders, vector<Texture*> ship_textures);
    };
}