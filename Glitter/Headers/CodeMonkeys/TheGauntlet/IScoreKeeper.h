#pragma once

namespace CodeMonkeys::TheGauntlet
{
    class IScoreKeeper
    {
        private:
            float score;
        
        public:
            IScoreKeeper();
            float get_score();
            void set_score(float score);
            void reset_score();
            void add_points(float points);
            void subtract_points(float points);
    };
}