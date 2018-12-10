#pragma once

#include <SFML/Audio.hpp>
#include "CodeMonkeys/TheGauntlet/IScoreKeeper.h"
#include "CodeMonkeys/Engine/UI/Text.h"
#include "glitter.hpp"
#include <string>

using namespace std;
using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::UI;

namespace CodeMonkeys::TheGauntlet::UI
{
    class ScoreDisplay : public Text
    {
    private:
        IScoreKeeper* measured_score_keeper = NULL;
        string label = "score: ";
    public:
        ScoreDisplay(IScoreKeeper* measured_score_keeper, string label, vec2 position, float size);
        virtual void update(float dt);
    };
}