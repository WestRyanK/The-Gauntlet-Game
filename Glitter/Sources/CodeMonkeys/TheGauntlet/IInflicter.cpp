#include "CodeMonkeys/TheGauntlet/IInflicter.h"

using CodeMonkeys::TheGauntlet::IInflicter;

IInflicter::IInflicter(unsigned int inflict_amount)
{
    this->inflict_amount = inflict_amount;
}

unsigned int IInflicter::get_inflict_amount()
{
    return this->inflict_amount;
}
void IInflicter::set_inflict_amount(unsigned int inflict_amount)
{
    this->inflict_amount = inflict_amount;
}


void IInflicter::inflict_damage(IDamageable* damageable)
{
    damageable->take_damage(this->inflict_amount);
}