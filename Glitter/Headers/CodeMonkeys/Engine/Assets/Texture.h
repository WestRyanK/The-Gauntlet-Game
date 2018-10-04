#pragma once

#include <string>

using namespace std;

namespace CodeMonkeys::TheGauntlet::Engine::Assets
{
    class Texture
    {
    private:
        unsigned int width;
        unsigned int height;
        unsigned int channel_count;
        unsigned char* data;
        string* texture_name;

    public:
        Texture(string texture_path);
        unsigned int get_width();
        unsigned int get_height();
        unsigned int get_channel_count();
        string* get_texture_name();
    }
};