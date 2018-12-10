#include "CodeMonkeys/TheGauntlet/Weapons/IInflicter.h"

using CodeMonkeys::TheGauntlet::Weapons::IInflicter;

IInflicter::IInflicter(int inflict_amount)
{
    this->inflict_amount = inflict_amount;
}

int IInflicter::get_inflict_amount()
{
    return this->inflict_amount;
}
void IInflicter::set_inflict_amount(int inflict_amount)
{
    this->inflict_amount = inflict_amount;
}


void IInflicter::inflict_damage(IDamageable* damageable)
{
    damageable->take_damage(this->inflict_amount);
}