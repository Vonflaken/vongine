#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texCoords;

uniform mat4 u_projMatrix;

out vec4 v_color;
out vec2 v_texCoords;

void main()
{
	gl_Position = u_projMatrix * vec4(a_position, 1.0);
	v_color = a_color;
	v_texCoords = a_texCoords;
}
