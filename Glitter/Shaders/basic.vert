#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 view_transform;
uniform mat4 projection_transform;
uniform mat4 object_transform;

void main()
{
    gl_Position = projection_transform * view_transform * object_transform * vec4(position, 1.0);
}
