#pragma once


namespace CodeMonkeys::TheGauntlet
{
    class IDamageable
    {
        private:
            unsigned int health;
        
        public:
            unsigned int get_health();
            void inflict_damage(unsigned int damage_amount);
            void on_death() = 0;
    }
}