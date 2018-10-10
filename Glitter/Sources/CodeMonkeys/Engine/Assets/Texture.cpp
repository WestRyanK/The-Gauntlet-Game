#include "Texture.h"
#include <string.h>
#include "NIE.h"

using namespace std;
using CodeMonkeys::Engine::Assets::Texture;

Texture::Texture(const char* texture_path)
{
    this->texture_path = texture_path;

    glGenTextures(1, &(this->texture_id)); 
    glBindTexture(GL_TEXTURE_2D, this->texture_id);  

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char* data = stbi_load(this->texture_path, &(this->width), &(this->height), &(this->channel_count), 0); 
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
        // glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        printf("Failed to load texture image: %s\n", texture_path);
    }
}

int Texture::get_width()
{
    return this->width;
}

int Texture::get_height()
{
    return this->height;
}

int Texture::get_channel_count()
{
    return this->channel_count;
}
unsigned int Texture::get_texture_id()
{
    return this->texture_id;
}

const char* Texture::get_texture_path()
{
    return this->texture_path;
}
