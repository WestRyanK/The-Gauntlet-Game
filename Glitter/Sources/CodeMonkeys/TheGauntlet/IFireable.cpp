#include "CodeMonkeys/TheGauntlet/IFireable.h"
#include <algorithm>

using CodeMonkeys::TheGauntlet::IFireable;

IFireable::IFireable(float recharge_delay, bool is_automatic_fire)
{
    this->recharge_delay = recharge_delay;
    this->is_automatic_fire = is_automatic_fire;
    this->recharge_time_elapsed = 0.0f;
    this->was_fire_held = true;

    this->recharge_timer.get_seconds_from_last_measurement();
}

void IFireable::pull_trigger()
{
    this->update_recharge_time();

    bool can_fire = this->is_automatic_fire || !this->was_fire_held;

    if (can_fire && this->recharge_time_elapsed >= this->recharge_delay)
    {
        this->on_fire();
        this->recharge_time_elapsed = 0.0f;
    }
    else
    {
        this->on_misfire();
    }

    this->was_fire_held = true;
}

void IFireable::update_recharge_time()
{
    this->recharge_time_elapsed += this->recharge_timer.get_seconds_from_last_measurement();
}

void IFireable::on_misfire()
{

}

void IFireable::release_trigger()
{
    this->was_fire_held = false;
}

float IFireable::get_recharge_delay()
{
    return this->recharge_delay;
}

float IFireable::get_recharge_time_remaining()
{
    this->update_recharge_time();
    return std::max(0.0f, this->recharge_delay - this->recharge_time_elapsed);
}