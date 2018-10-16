#version 330 core

in vec3 normal_2;
in vec2 uv_2;

out vec4 color_out;

uniform sampler2D texture_0;
uniform float ambient_strength;
uniform vec3 ambient_color;
uniform float directional_strength;
uniform vec3 directional_color;
uniform vec3 directional_direction;

void main()
{
    vec4 object_color = texture(texture_0, uv_2);
    // vec4 object_color = vec4(0.5f,0.5f, 0.5f, 0.5f  );
    vec4 ambient_out = object_color * ambient_strength * vec4(ambient_color, 1.0f);
    vec4 directional_out = object_color * vec4(directional_color * directional_strength * max(0.0f, dot(normal_2, directional_direction)), 1.0f);
    color_out = ambient_out + directional_out;
}