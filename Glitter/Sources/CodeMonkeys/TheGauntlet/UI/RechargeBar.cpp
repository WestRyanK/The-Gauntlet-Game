#include "CodeMonkeys/TheGauntlet/UI/RechargeBar.h"

using CodeMonkeys::TheGauntlet::RechargeBar;

RechargeBar::RechargeBar(ITriggerable* measured_triggerable, float x, float y, float width, float height) 
    : ProgressBar(new AnimatedTexture("Assets/UI/RechargeBar/recharge_bar", "png", 17),x, y, width, height)
{
    this->measured_triggerable = measured_triggerable;
}

void RechargeBar::update(float dt)
{
    ProgressBar::update(this->measured_triggerable->get_recharge_time_remaining(), this->measured_triggerable->get_recharge_delay(), false);
}