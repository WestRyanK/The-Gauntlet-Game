#include "CodeMonkeys/TheGauntlet/UI/RechargeBar.h"

using CodeMonkeys::TheGauntlet::RechargeBar;

RechargeBar::RechargeBar(ITriggerable* measured_triggerable, vec2 position, vec2 size)
    : ProgressBar(new AnimatedTexture("Assets/UI/RechargeBar/recharge_bar", "png", 17), position, size)
{
    this->measured_triggerable = measured_triggerable;
}

void RechargeBar::update(float dt)
{
    ProgressBar::update(this->measured_triggerable->get_recharge_time_remaining(), this->measured_triggerable->get_recharge_delay(), false);
}