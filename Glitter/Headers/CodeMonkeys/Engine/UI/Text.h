#pragma once

#include "CodeMonkeys/Engine/Engine/Quad.h"
#include "CodeMonkeys/Engine/Assets/Texture.h"
#include <string>
#include <map>

using namespace CodeMonkeys::Engine::Engine;
using namespace CodeMonkeys::Engine::Assets;
using namespace std;

namespace CodeMonkeys::Engine::UI
{
    class Text : public Quad
    {
    private:
        string text;
        vec2 position;
        float font_size;
        float character_spacing;
        float line_spacing;
        static void init();
        static map<char, Texture*> characters;
        void draw_character(char character, vec2 character_position);

    public:
        Text(string text, vec2 position, float font_size);
        virtual void draw();

        string get_text();
        void set_text(string text);
        vec2 get_position();
        void set_position(vec2 position);
        float get_font_size();
        void set_font_size(float font_size);
        float get_character_spacing();
        void set_character_spacing(float character_spacing);
        float get_line_spacing();
        void set_line_spacing(float line_spacing);

    };
}