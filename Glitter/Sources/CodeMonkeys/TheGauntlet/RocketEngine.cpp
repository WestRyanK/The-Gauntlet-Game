#include "CodeMonkeys/TheGauntlet/RocketEngine.h"

using CodeMonkeys::TheGauntlet::RocketEngine;

RocketEngine::RocketEngine(AnimatedTexture* texture, float width, float height, const char* sound_filename)
    : Billboard("rocket_engine", texture, width, height)
{
    this->sound_buffer = new sf::SoundBuffer();
    if (!this->sound_buffer->loadFromFile(sound_filename))
        printf("Could not load rocket engine sound file!\n");
    this->sound = new sf::Sound();
    this->sound->setLoop(true);
    this->sound->setBuffer(*this->sound_buffer);

    this->update(0);
}

void RocketEngine::update(float dt)
{
    Billboard::update(dt);
    this->update_billboard(dt);
    this->update_sound(dt);
}

void RocketEngine::update_billboard(float dt)
{
    AnimatedTexture* texture = (AnimatedTexture*)this->billboard_texture;
    if (this->is_accelerating)
    {
        this->current_frame += dt * this->acceleration_frame;
    }
    else
    {
        this->current_frame -= dt * this->deceleration_frame;
    }

    if (this->current_frame > texture->get_frame_count())
        this->current_frame = texture->get_frame_count();
    if (this->current_frame < 0)
        this->current_frame = 0;

    texture->set_current_frame(floor(this->current_frame));
}

void RocketEngine::update_sound(float dt)
{
    if (this->is_accelerating)
    {
        this->current_volume += dt * this->acceleration_volume;
        this->current_pitch += dt * this->acceleration_pitch;
    }
    else
    {
        this->current_volume -= dt * this->deceleration_volume;
        this->current_pitch -= dt * this->deceleration_pitch;
    }

    if (this->current_volume > this->max_volume)
        this->current_volume = this->max_volume;
    if (this->current_volume < this->min_volume)
        this->current_volume = this->min_volume;

    if (this->current_pitch > this->max_pitch)
        this->current_pitch = this->max_pitch;
    if (this->current_pitch < this->min_pitch)
        this->current_pitch = this->min_pitch;

    this->sound->setVolume(this->current_volume);
    this->sound->setPitch(this->current_pitch);
}

void RocketEngine::set_is_accelerating(bool is_accelerating)
{
    this->is_accelerating = is_accelerating;
}

void RocketEngine::play()
{
    this->sound->play();
}

void RocketEngine::stop()
{
    this->sound->stop();
}


void RocketEngine::set_max_volume(float max_volume)
{
    this->max_volume = max_volume;
}

void RocketEngine::set_min_volume(float min_volume)
{
    this->min_volume = min_volume;
}

float RocketEngine::get_max_volume()
{
    return this->max_volume;
}

float RocketEngine::get_min_volume()
{
    return this->min_volume;
}

void RocketEngine::set_acceleration_volume(float acceleration_volume)
{
    this->acceleration_volume = acceleration_volume;
}

void RocketEngine::set_deceleration_volume(float deceleration_volume)
{
    this->deceleration_volume = deceleration_volume;
}

float RocketEngine::get_acceleration_volume()
{
    return this->acceleration_volume;
}

float RocketEngine::get_deceleration_volume()
{
    return this->deceleration_volume;
}


void RocketEngine::set_max_pitch(float max_pitch)
{
    this->max_pitch = max_pitch;
}

void RocketEngine::set_min_pitch(float min_pitch)
{
    this->min_pitch = min_pitch;
}

float RocketEngine::get_max_pitch()
{
    return this->max_pitch;
}

float RocketEngine::get_min_pitch()
{
    return this->min_pitch;
}

void RocketEngine::set_acceleration_pitch(float acceleration_pitch)
{
    this->acceleration_pitch = acceleration_pitch;
}

void RocketEngine::set_deceleration_pitch(float deceleration_pitch)
{
    this->deceleration_pitch = deceleration_pitch;
}

float RocketEngine::get_acceleration_pitch()
{
    return this->acceleration_pitch;
}

float RocketEngine::get_deceleration_pitch()
{
    return this->deceleration_pitch;
}


void RocketEngine::set_acceleration_frame(float acceleration_frame)
{
    this->acceleration_frame = acceleration_frame;
}

void RocketEngine::set_deceleration_frame(float deceleration_frame)
{
    this->deceleration_frame = deceleration_frame;
}

float RocketEngine::get_acceleration_frame()
{
    return this->acceleration_frame;
}

float RocketEngine::get_deceleration_frame()
{
    return this->deceleration_frame;
}