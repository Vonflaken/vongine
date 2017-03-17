#include "VGGLProgram.h"
#include "rendering/VGShader.h"
#include <vector>
#include "base/VGLogger.h"

NS_VG_BEGIN

GLProgram::GLProgram()
: _program(0)
{}

GLProgram::~GLProgram()
{
	DeleteProgram();
}

bool GLProgram::Build(const Shader* vertexShader, const Shader* fragmentShader)
{
	// Get both shader identifiers
	GLuint vertexName = vertexShader->GetName();
	GLuint fragmentName = fragmentShader->GetName();

	if (!vertexName || !fragmentName) // Early exist if one of the shaders is invalid
		return false;

	if (_program) // Early exist if program is already built
		return true;

	bool success = false; // Result of building

	// Create program
	_program = glCreateProgram();

	// Attach both shaders
	glAttachShader(_program, vertexName);
	glAttachShader(_program, fragmentName);

	// Link program
	glLinkProgram(_program);

	// Detach shaders after link
	glDetachShader(_program, vertexName);
	glDetachShader(_program, fragmentName);

	// Handle linking errors
	GLint isLinked = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, (int *)&isLinked); // Get link status
	if (isLinked == GL_TRUE)
	{
		success = true;
	}
	else
	{
		// Linking error

		GLint maxLength = 0;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength); // Get info log string length

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_program, maxLength, &maxLength, &infoLog[0]); // Get info log string

		VGLOG("%s", &infoLog[0]); // Log error info
	}

	if (!success)
		DeleteProgram(); // Cleanup program if building failed

	return success;
}

void GLProgram::DeleteProgram()
{
	glDeleteProgram(_program);
	_program = 0;
}

NS_VG_END
