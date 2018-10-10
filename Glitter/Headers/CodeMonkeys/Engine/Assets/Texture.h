#pragma once

#include <string>
#include "glitter.hpp"

using namespace std;

namespace CodeMonkeys::Engine::Assets
{
    class Texture
    {
    private:
        int width;
        int height;
        int channel_count;
        unsigned int texture_id;
        const char* texture_path;

    public:
        Texture(const char* texture_path);
        int get_width();
        int get_height();
        int get_channel_count();
        unsigned int get_texture_id();
        const char* get_texture_path();
    };
}