#include "CodeMonkeys/TheGauntlet/UI/HealthBar.h"

using CodeMonkeys::TheGauntlet::HealthBar;

HealthBar::HealthBar(IDamageable* measured_damageable, vec2 position, vec2 size) 
    : ProgressBar(new AnimatedTexture("Assets/UI/HealthBar/health_bar", "png", 13), position, size)
{
    this->measured_damageable = measured_damageable;

    this->sound_buffer = new sf::SoundBuffer();
    this->sound = new sf::Sound();
    this->sound->setVolume(50);
    if (!this->sound_buffer->loadFromFile("Assets/UI/HealthBar/alarm.wav"))
        printf("Could not load 'alarm.wav' file!\n");
    this->sound->setBuffer(*this->sound_buffer);
}

void HealthBar::update(float dt)
{
    float percent = this->measured_damageable->get_health() / (float)this->measured_damageable->get_max_health();
    if (percent <= 0.0f)
    {
        if (this->sound->getStatus() == sf::Sound::Playing)
            this->sound->stop();
    }
    else if (percent < this->alarm_percent && this->sound->getStatus() != sf::Sound::Playing)
        this->sound->play();
    else if (percent > this->alarm_percent && this->sound->getStatus() == sf::Sound::Playing)
        this->sound->stop();

    ProgressBar::update(this->measured_damageable->get_health(), this->measured_damageable->get_max_health(), true);
}

void HealthBar::set_alarm_percent(float alarm_percent)
{
    this->alarm_percent = alarm_percent;
}

float HealthBar::get_alarm_percent()
{
    return this->alarm_percent;
}