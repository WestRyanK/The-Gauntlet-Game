#version 330 core
layout (location = 0) in vec3 position;

void main()
{
	// The divide by 10 was just so the model could appear on screen. You should remove it
    gl_Position = vec4(position.x / 10, position.y / 10, position.z / 10, 1.0);
}
