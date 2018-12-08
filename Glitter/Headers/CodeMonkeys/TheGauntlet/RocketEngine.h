#pragma once

#include <SFML/Audio.hpp>
#include "CodeMonkeys/Engine/Objects/Billboard.h"
#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"

using namespace CodeMonkeys::Engine::Objects;
using namespace CodeMonkeys::Engine::Assets;

namespace CodeMonkeys::TheGauntlet
{
    class RocketEngine : public Billboard
    {
    private:
        sf::SoundBuffer* sound_buffer;
        sf::Sound* sound;
        bool is_accelerating = false;

        float max_volume = 100;
        float min_volume = 0;
        float current_volume = min_volume;
        float acceleration_volume = 1;
        float deceleration_volume = 1;

        float max_pitch = 1.5f;
        float min_pitch = 0.25f;
        float current_pitch = min_pitch;
        float acceleration_pitch = 1;
        float deceleration_pitch = 1;

        float current_frame = 0;
        float acceleration_frame = 1;
        float deceleration_frame = 1;
        bool twitch_frame = false;

    protected:
        void update_billboard(float dt);
        void update_sound(float dt);
    public:
        RocketEngine(AnimatedTexture* texture, float width, float height, const char* sound_filename);
        virtual void update(float dt);
        void set_is_accelerating(bool is_accelerating);
        void play();
        void stop();

        void set_max_volume(float max_volume);
        void set_min_volume(float min_volume);
        float get_max_volume();
        float get_min_volume();
        void set_acceleration_volume(float acceleration_volume);
        void set_deceleration_volume(float deceleration_volume);
        float get_acceleration_volume();
        float get_deceleration_volume();

        void set_max_pitch(float max_pitch);
        void set_min_pitch(float min_pitch);
        float get_max_pitch();
        float get_min_pitch();
        void set_acceleration_pitch(float acceleration_pitch);
        void set_deceleration_pitch(float deceleration_pitch);
        float get_acceleration_pitch();
        float get_deceleration_pitch();

        void set_acceleration_frame(float acceleration_frame);
        void set_deceleration_frame(float deceleration_frame);
        float get_acceleration_frame();
        float get_deceleration_frame();
        
        void set_twitch_frame(bool twitch_frame);
        bool get_twitch_frame();
    };
}