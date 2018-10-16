#version 330 core

in vec3 normal_2;
in vec2 uv_2;

out vec4 color_out;

uniform sampler2D texture_0;
uniform float ambient_strength;
uniform vec3 ambient_color;

void main()
{
    vec4 object_color = texture(texture_0, uv_2);
    // color_out = object_color;
    if (ambient_strength > 0.0f)
    {
        vec4 ambient_out = object_color * ambient_strength * vec4(ambient_color, 1.0f);
        color_out = ambient_out;
    }
    else
    {
        color_out = object_color;
    }
}