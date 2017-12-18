#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;

void main()
{
	gl_Position = u_projMatrix * u_viewMatrix * vec4(a_position, 1.0);
}
