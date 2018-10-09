#include "Texture.h"
#include "NIE.h"

using CodeMonkeys::Engine::Assets::Texture;

Texture::Texture(string texture_path)
{
    throw NotImplementedException("Texture::constructor");
}

unsigned int Texture::get_width()
{
    return this->width;
}

unsigned int Texture::get_height()
{
    return this->height;
}

unsigned int Texture::get_channel_count()
{
    return this->channel_count;
}

string* Texture::get_texture_name()
{
    return this->texture_name;
}
