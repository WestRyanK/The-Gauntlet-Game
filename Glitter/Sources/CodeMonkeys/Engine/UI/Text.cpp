#include "CodeMonkeys/Engine/UI/Text.h"
#include <string>

using CodeMonkeys::Engine::UI::Text;
using namespace std;

Text::Text(string text, vec2 position, float font_size) : Quad(0,0,0,0)
{
    this->text = text;
    this->position = position;
    this->font_size = font_size;
    this->character_spacing = 1;

    if (Text::characters.size() == 0)
        Text::init();
}

void Text::init()
{

}

string Text::get_text()
{
    return this->text;
}

void Text::set_text(string text)
{
    this->text = text;
}

vec2 Text::get_position()
{
    return this->position;
}

void Text::set_position(vec2 position)
{
    this->position = position;
}

float Text::get_font_size()
{
    return this->font_size;
}

void Text::set_font_size(float font_size)
{
    this->font_size = font_size;
}

float Text::get_character_spacing()
{
    return this->character_spacing;
}
void Text::set_character_spacing(float character_spacing)
{
    this->character_spacing = character_spacing;
}

float Text::get_line_spacing()
{
    return this->line_spacing;
}

void Text::set_line_spacing(float line_spacing)
{
    this->line_spacing = line_spacing;
}

void Text::draw()
{
    vec2 current_position = this->position;
    for (int i = 0; i < this->text.size(); i++)
    {
        if (this->text[i] == '\n')
        {
            current_position.x = this->position.x;
            current_position.y += this->font_size * this->line_spacing;
        }
        else
        {
            this->draw_character(this->text[i], current_position);
        }
        current_position.x += this->font_size * this->character_spacing;
    }
}

void Text::draw_character(char character, vec2 character_position)
{
    this->
}