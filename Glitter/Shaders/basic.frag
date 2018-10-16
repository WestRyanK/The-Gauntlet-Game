#version 330 core

in vec3 normal_2;
in vec2 uv_2;

out vec4 color_out;

uniform sampler2D texture_0;

void main()
{
    // color_out = texture(texture_0, uv_2);
    color_out = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}