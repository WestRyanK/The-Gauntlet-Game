#pragma once 

#include "CodeMonkeys/Engine/Assets/Texture.h"

namespace CodeMonkeys::Engine::Assets
{
    class AnimatedTexture : public Texture
    {
    private:
        Texture** frames;
        int frame_count = 0;
        int current_frame = 0;
        int animation_speed = 1;
    public:
        AnimatedTexture(const char* filename, const char* extension, int count);
        void set_current_frame(int frame);
        int get_current_frame();
        int get_frame_count();

        int get_width();
        int get_height();
        int get_channel_count();
        unsigned int get_texture_id();
        const char* get_texture_path();
        void set_animation_speed(int animation_speed);
        virtual void update(float dt);
        virtual void reset();
    };
}