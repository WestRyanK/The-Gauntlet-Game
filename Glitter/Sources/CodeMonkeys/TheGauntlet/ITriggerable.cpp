#include "CodeMonkeys/TheGauntlet/ITriggerable.h"
#include <algorithm>

using CodeMonkeys::TheGauntlet::ITriggerable;

ITriggerable::ITriggerable(float recharge_delay, bool is_automatic_fire)
{
    this->recharge_delay = recharge_delay;
    this->is_automatic_fire = is_automatic_fire;
    this->recharge_time_elapsed = this->recharge_delay;
    this->was_trigger_held = true;

    this->recharge_timer.get_seconds_from_last_measurement();
}

void ITriggerable::pull_trigger()
{
    this->update_recharge_time();

    bool can_fire = this->is_automatic_fire || !this->was_trigger_held;

    if (can_fire && this->recharge_time_elapsed >= this->recharge_delay)
    {
        this->on_fire();
        this->recharge_time_elapsed = 0.0f;
    }
    else
    {
        this->on_misfire();
    }

    this->was_trigger_held = true;
}

void ITriggerable::update_recharge_time()
{
    this->recharge_time_elapsed += this->recharge_timer.get_seconds_from_last_measurement();
}

void ITriggerable::on_misfire()
{

}

void ITriggerable::release_trigger()
{
    this->was_trigger_held = false;
}

float ITriggerable::get_recharge_delay()
{
    return this->recharge_delay;
}

float ITriggerable::get_recharge_time_remaining()
{
    this->update_recharge_time();
    return std::max(0.0f, this->recharge_delay - this->recharge_time_elapsed);
}