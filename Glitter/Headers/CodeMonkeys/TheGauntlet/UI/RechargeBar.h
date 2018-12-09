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
        RechargeBar(ITriggerable* measured_triggerable, vec2 position, vec2 size);
        virtual void update(float dt);
    };
}