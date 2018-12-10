#pragma once

#include <SFML/Audio.hpp>
// #include "CodeMonkeys/TheGauntlet/ITimeKeeper.h"
#include "CodeMonkeys/Engine/UI/Text.h"
#include "glitter.hpp"
#include <string>

using namespace std;
// using namespace CodeMonkeys::TheGauntlet;
using namespace CodeMonkeys::Engine::UI;

namespace CodeMonkeys::TheGauntlet::UI
{
    class TimeDisplay : public Text
    {
    private:
        // ITimeKeeper* measured_time_keeper = NULL;
        float elapsed_time;
        float start_time;
        float hurry_time_left;
        float music_accelerate_factor;
        sf::Music* background_music;
        const int MINUTE = 60;
    public:
        TimeDisplay(sf::Music* background_music, float hurry_time_left, float music_accelerate_factor, float start_time, vec2 position, float size);
        // TimeDisplay(ITimeKeeper* measured_time_keeper, vec2 position, float size);
        virtual void update(float dt);
    };
}