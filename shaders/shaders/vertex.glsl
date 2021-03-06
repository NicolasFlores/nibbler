#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexColor;

flat out vec3 myColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    // gl_Position = projection * view * vec4(aPos, 1.0);
    // gl_Position = projection * vec4(aPos, 1.0);
    gl_Position = view * vec4(aPos, 1.0);
	myColor = aTexColor;
} 
