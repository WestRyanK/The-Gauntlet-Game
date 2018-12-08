#pragma once

#include <SFML/Audio.hpp>
#include "CodeMonkeys/TheGauntlet/Weapons/IDamageable.h"
#include "CodeMonkeys/Engine/UI/ProgressBar.h"

using namespace CodeMonkeys::TheGauntlet::Weapons;
using namespace CodeMonkeys::Engine::UI;

namespace CodeMonkeys::TheGauntlet
{
    class HealthBar : public ProgressBar
    {
    private:
        IDamageable* measured_damageable = NULL;
        sf::Sound* sound = NULL;
        sf::SoundBuffer* sound_buffer = NULL;
        float alarm_percent = 0.0f;
    public:
        HealthBar(IDamageable* measured_damageable, float x, float y, float width, float height);
        virtual void update(float dt);
        void set_alarm_percent(float alarm_percent);
        float get_alarm_percent();
    };
}