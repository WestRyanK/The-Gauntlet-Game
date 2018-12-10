#pragma once


namespace CodeMonkeys::TheGauntlet::Weapons
{
    class IDamageable
    {
        private:
            int health;
            int initial_health;
            int max_health;
        
        public:
            IDamageable(unsigned int initial_health, unsigned int max_health);
            int get_health();
            int get_max_health();
            void take_damage(unsigned int damage_amount);
            void heal_health(unsigned int heal_amount);
            void reset_health();
            virtual void on_death() = 0;
    };
}