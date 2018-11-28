#pragma once


namespace CodeMonkeys::TheGauntlet
{
    class IInflicter
    {
        private:
            unsigned int inflict_amount;
        
        public:
            IInflicter(unsigned int inflict_amount);
            unsigned int get_inflict_amount();
            void set_inflict_amount(unsigned int inflict_amount);
    };
}