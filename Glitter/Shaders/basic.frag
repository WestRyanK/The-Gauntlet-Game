#version 330 core
#define MAX_DIRECTIONAL 4
#define MAX_AMBIENT 1

in vec3 normal_2;
in vec2 uv_2;

out vec4 color_out;

uniform sampler2D texture_0;
uniform int directional_count;
uniform struct directional_light
{
    float strength;
    vec3 color;
    vec3 direction;
} directional[MAX_DIRECTIONAL];

uniform int ambient_count;
uniform struct ambient_light
{
    float strength;
    vec3 color;
} ambient[MAX_AMBIENT];

vec4 apply_ambient(vec4 object_color, ambient_light light)
{
    vec4 ambient_out = object_color * light.strength * vec4(light.color, 1.0f);
    return ambient_out;
}

vec4 apply_directional(vec4 object_color, directional_light light)
{
    vec3 r = 2 * normal_2 * dot(normal_2, light.direction) - light.direction;

    // vec4 phong_reflect_out = light.color * phong_color * pow(max(0.0f, dot(e, r)), phong_exponent);

    vec4 directional_out = object_color * vec4(light.color * light.strength * max(0.0f, dot(normal_2, light.direction)), 1.0f);
    // directional_out += phong_reflect_out;
    return directional_out;
}

void main()
{
    vec4 object_color = texture(texture_0, uv_2);
    // vec4 object_color = vec4(0.5f,0.5f, 0.5f, 0.5f);

    color_out = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    for (int i = 0; i < ambient_count; ++i)
    {
        color_out += apply_ambient(object_color, ambient[i]);
    }
    for (int i = 0; i < directional_count; i++)
    {
        color_out += apply_directional(object_color, directional[i]);
    }

    // vec4 ambient_out = object_color * ambient_strength * vec4(ambient_color, 1.0f);
    // vec4 directional_out = object_color * vec4(directional_color * directional_strength * max(0.0f, dot(normal_2, directional_direction)), 1.0f);
    // color_out = ambient_out + directional_out;
}