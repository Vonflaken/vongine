in vec4 a_position;
in vec2 a_texCoords;
in vec4 a_color;

uniform mat4 u_projMatrix;

out vec4 v_color;
out vec2 v_texCoords;

void main()
{
	gl_Position = u_ProjMatrix * a_position;
	o_color = a_color;
	o_texCoords = a_texCoords;
}
