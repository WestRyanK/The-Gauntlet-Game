#pragma once

#include <string>
#include "glitter.hpp"

using namespace std;

namespace CodeMonkeys::Engine::Assets
{
    class Texture
    {
    protected:
        int width;
        int height;
        int channel_count;
        unsigned int texture_id;
        const char* texture_path;

    public:
        Texture(const char* texture_path);
        virtual int get_width();
        virtual int get_height();
        virtual int get_channel_count();
        virtual unsigned int get_texture_id();
        virtual const char* get_texture_path();
        virtual void update(float dt);
        virtual void reset();
        virtual Texture* clone();
    };
}