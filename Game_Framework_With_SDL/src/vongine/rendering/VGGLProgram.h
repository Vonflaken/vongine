#ifndef __VGGLPROGRAM_H__
#define __VGGLPROGRAM_H__

#include "VGMacros.h"
#include "ogl/glew.h"

NS_VG_BEGIN

enum class GLProgramName // Use as a program identifier
{
	POSITIONTEXTURECOLOR_noMVP
};

class Shader;

/// GLProgram is built with a vertex shader and a fragment shader
class __declspec(dllexport) GLProgram
{
public:
	GLProgram();
	virtual ~GLProgram();

	/// Create gl program from vert/frag shaders filenames
	bool Build(const char* vertexFilename, const char* fragmentFilename);
	/// Create gl program from pointers to vert/frag shader objects
	bool Build(const Shader* vertexShader, const Shader* fragmentShader);

private:
	/// Cleanup program object
	/// Set _program value to 0
	void DeleteProgram();

private:
	GLuint _program;
};

NS_VG_END

#endif // __VGGLPROGRAM_H__
