#pragma once

#include "CodeMonkeys/TheGauntlet/Weapons/IDamageable.h"

namespace CodeMonkeys::TheGauntlet::Weapons
{
    class IInflicter
    {
        private:
            int inflict_amount;
        
        public:
            IInflicter(int inflict_amount);
            int get_inflict_amount();
            void set_inflict_amount(int inflict_amount);
            void inflict_damage(IDamageable* damageable);
    };
}