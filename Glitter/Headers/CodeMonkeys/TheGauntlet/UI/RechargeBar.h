#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/ITriggerable.h"
#include "CodeMonkeys/Engine/UI/ProgressBar.h"

using namespace CodeMonkeys::TheGauntlet::Weapons;
using namespace CodeMonkeys::Engine::UI;

namespace CodeMonkeys::TheGauntlet
{
    class RechargeBar : public ProgressBar
    {
    private:
        ITriggerable* measured_triggerable = NULL;
    public:
        RechargeBar(ITriggerable* measured_triggerable, float x, float y, float width, float height);
        virtual void update(float dt);
    };
}