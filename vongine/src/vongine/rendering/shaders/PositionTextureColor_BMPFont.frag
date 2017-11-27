#version 330 core

in vec4 v_color;
in vec2 v_texCoords;

uniform sampler2D u_texture; // Greyscale texture

void main()
{
	vec4 pixel = texture2D(u_texture, v_texCoords);

	gl_FragColor = vec4(pixel.r) * v_color; // Use R channel as greyscale and alpha, gets smoother glyph aliasing blending the intermediate grey values from gliph outline
}
