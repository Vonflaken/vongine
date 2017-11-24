#ifndef __VGGLPROGRAM_H__
#define __VGGLPROGRAM_H__

#include "VGMacros.h"
#include "ogl/glew.h"
#include "rendering/VGGLProgramState.h"
#include <memory>

NS_VG_BEGIN

enum class GLProgramName // Use as a program identifier
{
	POSITIONTEXTURECOLOR_noMVP, // "PositionTextureColor_noMVP.vert" + "PositionTextureColor.frag"
	POSITIONTEXTURECOLOR_noMVP_BMPFont // "PositionTextureColor_noMVP.vert", "PositionTextureColor_BMPFont.frag"
};

class Shader;

/// GLProgram is built with a vertex shader and a fragment shader
/// Tells graphic device how draw the thing
class DLLAPI GLProgram
{
public:
	GLProgram();
	virtual ~GLProgram();

	/// Create gl program from vert/frag shaders filenames
	bool Build(const char* vertexFilename, const char* fragmentFilename);
	/// Create gl program from pointers to vert/frag shader objects
	bool Build(const Shader* vertexShader, const Shader* fragmentShader);

	/// Use this program for rendering pipeline
	void Use();

	GLProgramState& State() { return _programState; }
	const GLProgramState& ConstState() const { return _programState; }

	GLuint GetProgramID() const { return _program; }

private:
	/// Free graphic resources
	/// Invalid the program
	void DeleteProgram();

private:
	GLuint _program;
	GLProgramState _programState;
};

NS_VG_END

#endif // __VGGLPROGRAM_H__
