#pragma once

#include <vector>
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Portal.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Ship.h"

using namespace std;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class PortalFactory
    {
    private:
        static vector<Material*> materials;
    public:
        static Portal* create_portal(Ship* ship);
        static void init(ShaderProgram* shader);
    };
}