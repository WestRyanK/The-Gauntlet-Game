#pragma once

#include <vector>
#include "CodeMonkeys/Engine/Assets/ShaderProgram.h"
#include "CodeMonkeys/TheGauntlet/GameObjects/Portal.h"

using namespace std;

namespace CodeMonkeys::TheGauntlet::GameObjects
{
    class PortalFactory
    {
    private:
        static vector<Material*> materials;
    public:
        static Portal* create_portal();
        static void init(ShaderProgram* shader);
    };
}