#ifndef __VGSHADER_H__
#define __VGSHADER_H__

#include "VGMacros.h"

#include "ogl/glew.h"

NS_VG_BEGIN

enum ShaderType
{
	VERTEX = GL_VERTEX_SHADER, 
	FRAGMENT = GL_FRAGMENT_SHADER
};

class DLLAPI Shader
{
public:
	Shader();
	/// Delete shader
	virtual ~Shader();

	/// Creates and compiles shader object
	/// Returns whereas the shader compilation was correct or not
	bool Compile(const char* filename, const ShaderType type);

	GLuint GetName() const { return _name; }

private:
	/// Delete gl shader resource
	/// Set _name value to 0
	void DeleteShader();

private:
	GLuint _name;
};

NS_VG_END

#endif // __VGSHADER_H__

