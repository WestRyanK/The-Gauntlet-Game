#include "CodeMonkeys/TheGauntlet/UI/ScoreDisplay.h"
#include <sstream>
#include <iostream>

using CodeMonkeys::TheGauntlet::UI::ScoreDisplay;

ScoreDisplay::ScoreDisplay(IScoreKeeper* measured_score_keeper, string label, vec2 position, float size)
    : Text(label, position, size)
{
    this->measured_score_keeper = measured_score_keeper;
    this->label = label;
}

void ScoreDisplay::update(float dt)
{
    float score = this->measured_score_keeper->get_score();

    std::ostringstream ss;
    ss << this->label << score;
    this->set_text(ss.str());
}