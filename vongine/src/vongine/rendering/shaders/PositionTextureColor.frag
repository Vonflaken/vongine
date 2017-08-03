#version 330 core

in vec4 v_color;
in vec2 v_texCoords;

uniform sampler2D u_texture;

void main()
{
	gl_FragColor = texture2D(u_texture, v_texCoords) * v_color;
}
