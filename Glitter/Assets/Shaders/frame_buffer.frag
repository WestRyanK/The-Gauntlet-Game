#version 330 core

in vec2 uv_2;

out vec4 color_out;

uniform sampler2D rendered_texture;

void main(){
    color_out = texture(rendered_texture, uv_2);
}