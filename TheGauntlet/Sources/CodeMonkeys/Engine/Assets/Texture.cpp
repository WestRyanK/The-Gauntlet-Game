#include "Texture.h"
#include <string.h>
#include "NIE.h"

using namespace std;
using CodeMonkeys::Engine::Assets::Texture;

Texture::Texture(const char* texture_path)
{
    if (texture_path != NULL)
    {
        this->texture_path = texture_path;

        glGenTextures(1, &(this->texture_id)); 
        glBindTexture(GL_TEXTURE_2D, this->texture_id);  

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        unsigned char* data = stbi_load(this->texture_path, &(this->width), &(this->height), &(this->channel_count), 0); 
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glBindTexture(GL_TEXTURE_2D, 0);
            // glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
        else // if (texture_path != NULL)
        {
            printf("Failed to load texture image: %s\n", texture_path);
        }
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

void Texture::update(float dt)
{

}

void Texture::reset()
{

}

Texture* Texture::clone()
{
    Texture* texture_clone = new Texture(NULL);
    texture_clone->width = this->width;
    texture_clone->height = this->height;
    texture_clone->channel_count = this->channel_count;
    texture_clone->texture_id = this->texture_id;
    texture_clone->texture_path = this->texture_path;
    return texture_clone;
}