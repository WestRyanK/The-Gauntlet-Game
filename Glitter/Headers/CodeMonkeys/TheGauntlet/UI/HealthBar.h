#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/IDamageable.h"
#include "CodeMonkeys/Engine/UI/ProgressBar.h"

using namespace CodeMonkeys::TheGauntlet::Weapons;
using namespace CodeMonkeys::Engine::UI;

namespace CodeMonkeys::TheGauntlet
{
    class HealthBar : public ProgressBar
    {
    private:
        IDamageable* measured_damageable = NULL;
    public:
        HealthBar(IDamageable* measured_damageable, float x, float y, float width, float height);
        virtual void update(float dt);
    };
}