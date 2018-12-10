#include "CodeMonkeys/TheGauntlet/UI/TimeDisplay.h"
#include "CodeMonkeys/Engine/Events/EventDispatcher.h"
#include <sstream>
#include <iostream>

using CodeMonkeys::TheGauntlet::UI::TimeDisplay;

TimeDisplay::TimeDisplay(sf::Music* background_music, float hurry_time_left, float music_accelerate_factor, float start_time, vec2 position, float size)
    : Text("", position, size)
{

    this->music_accelerate_factor = music_accelerate_factor;
    this->background_music = background_music;
    this->hurry_time_left = hurry_time_left;
    // this->measured_time_keeper = measured_time_keeper;
    this->start_time = start_time;
    this->elapsed_time = 0;
}

void TimeDisplay::update(float dt)
{
    this->elapsed_time += dt;
    char buffer[20] = { 0 };

    float time_remaining = this->start_time - this->elapsed_time;
    int minutes_remaining = time_remaining / MINUTE;
    float seconds_remaining = time_remaining - minutes_remaining * MINUTE;
    sprintf(buffer, "%02.2f", seconds_remaining);
    // sprintf(buffer, "%02d:%02.2f", minutes_remaining, seconds_remaining);

    string time_str(buffer);
    this->set_text(time_str);

    if (time_remaining <= this->hurry_time_left)
        this->background_music->setPitch(this->background_music->getPitch() + this->music_accelerate_factor * dt);

    if (time_remaining <= 0)
        CodeMonkeys::Engine::Events::EventDispatcher::get_instance().report_event("time_up");
}