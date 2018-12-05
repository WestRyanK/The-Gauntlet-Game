#include "CodeMonkeys/Engine/Assets/AnimatedTexture.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"
#include <sstream>
#include <string>
#include <iostream>

using CodeMonkeys::Engine::Assets::AnimatedTexture;
using namespace CodeMonkeys::Engine::Assets;

AnimatedTexture::AnimatedTexture(const char* filename, const char* extension, int count) : Texture(NULL)
{
    if (filename != NULL && extension != NULL && count > 0)
    {
        this->frames = new Texture*[count] { 0 };
        for (int i = 0; i < count; i++)
        {
            std::ostringstream os;
            os << filename << "_" << i << "." << extension;
            string s = os.str();
            Texture* texture = new Texture(s.c_str());
            this->frames[i] = texture;
        }

        this->current_frame = 0;
        this->frame_count = count;
    }
}

void AnimatedTexture::set_current_frame(int frame)
{
    this->current_frame = frame;
}

int AnimatedTexture::get_current_frame()
{
    return this->current_frame;
}

int AnimatedTexture::get_frame_count()
{
    return this->frame_count;
}

int AnimatedTexture::get_width()
{
    return this->frames[this->current_frame]->get_width();
}

int AnimatedTexture::get_height()
{
    return frames[this->current_frame]->get_height();
}

int AnimatedTexture::get_channel_count()
{
    return frames[this->current_frame]->get_channel_count();
}

unsigned int AnimatedTexture::get_texture_id()
{
    return frames[this->current_frame]->get_texture_id();
}

const char* AnimatedTexture::get_texture_path()
{
    return frames[this->current_frame]->get_texture_path();
}

void AnimatedTexture::update(float dt)
{
    this->set_current_frame((this->current_frame + this->animation_speed) % this->frame_count);
}

void AnimatedTexture::set_animation_speed(int animation_speed)
{
    this->animation_speed = animation_speed;
}

void AnimatedTexture::reset()
{
    this->set_current_frame(0);
}

Texture* AnimatedTexture::clone()
{
    AnimatedTexture* texture_clone = new AnimatedTexture(NULL, NULL, 0);
    texture_clone->frames = this->frames;
    texture_clone->frame_count = this->frame_count;
    texture_clone->current_frame = 0;
    texture_clone->animation_speed = this->animation_speed;
    return texture_clone;
}