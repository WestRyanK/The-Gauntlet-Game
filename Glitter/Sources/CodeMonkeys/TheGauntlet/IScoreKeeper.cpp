#include "CodeMonkeys/TheGauntlet/IScoreKeeper.h"

using CodeMonkeys::TheGauntlet::IScoreKeeper;

IScoreKeeper::IScoreKeeper()
{
    this->reset_score();
}

float IScoreKeeper::get_score()
{
    return this->score;
}

void IScoreKeeper::set_score(float score)
{
    this->score = score;
}

void IScoreKeeper::reset_score()
{
    this->score = 0;
}

void IScoreKeeper::add_points(float points)
{
    this->score += points;
}

void IScoreKeeper::subtract_points(float points)
{
    this->score -= points;
}