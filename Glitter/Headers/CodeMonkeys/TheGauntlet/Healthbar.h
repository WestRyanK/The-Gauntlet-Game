#pragma once

#include "CodeMonkeys/Engine/Engine/Quad.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/TheGauntlet/Weapons/IDamageable.h"

using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::Engine::Assets;
using namespace CodeMonkeys::TheGauntlet::Weapons;

namespace CodeMonkeys::TheGauntlet
{
    class Healthbar : public Quad
    {
    private:
        AnimatedTexture* healthbar_texture = NULL;
        IDamageable* measured_damageable = NULL;
    public:
        Healthbar(IDamageable* measured_damageable, float x, float y, float width, float height);
        virtual void update(float dt);
    };
}