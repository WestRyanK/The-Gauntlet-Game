#include "CodeMonkeys/TheGauntlet/IDamageable.h"

using CodeMonkeys::TheGauntlet::IDamageable;

IDamageable::IDamageable(unsigned int initial_health, unsigned int max_health)
{
    this->initial_health = initial_health;
    this->reset_health();
}

unsigned int IDamageable::get_health()
{
    return this->health;
}

void IDamageable::inflict_damage(unsigned int damage_amount)
{
    this->health -= damage_amount;
    this->max_health = max_health;

    if (this->health <= 0)
    {
        this->on_death();
    }
}

void IDamageable::heal_damamge(unsigned int heal_amount)
{
    this->health += heal_amount;

    if (this->health > this->max_health)
    {
        this->health = this->max_health;
    }
}

void IDamageable::reset_health()
{
    this->health = this->initial_health;
}