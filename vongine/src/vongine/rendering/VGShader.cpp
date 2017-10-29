#include "VGShader.h"
#include "platform/VGFile.h"
#include "base/VGLogger.h"
#include "base/VGUtils.h"

#include <vector>

NS_VG_BEGIN

using namespace utils;

Shader::Shader()
: _name(0)
{}

Shader::~Shader()
{
	// Shader deletion is deferred until shader is no longer attached to any program object
	DeleteShader();
}

/// Creates shader object of type required and compile it
/// Shader source from filename
bool Shader::Compile(const char* filename, const ShaderType type)
{
	if (_name) // Don't continue if shader is already created
		return true;

	bool success = false; // Result of shader compilation

	// Create empty shader object
	_name = glCreateShader(type);
	
	// Read shader file
	File shaderFile(filename, FileMode::READ);
	if (shaderFile.IsOpen())
	{
		int64 shaderFileSize = shaderFile.Size();
		auto shaderTextBuff = std::unique_ptr<unsigned char, VG_Free_Deleter>((unsigned char*)malloc(shaderFileSize)); // Reserve enough memory for storing shader text
		int64 readBytesCount = shaderFile.ReadBytes(shaderTextBuff.get(), shaderFileSize);
		if (readBytesCount == shaderFileSize)
		{
			unsigned char* shaderTextBuffPtr = shaderTextBuff.get();
			// Feed shader with shader text
			glShaderSource(_name, 1, (GLchar**)&shaderTextBuffPtr, (GLint*)&shaderFileSize);

			// Compile shader
			glCompileShader(_name);

			// Handle compilation error
			GLint isCompiled = 0;
			glGetShaderiv(_name, GL_COMPILE_STATUS, &isCompiled); // Get compilation state

			if (isCompiled == GL_TRUE)
			{
				success = true;
			}
			else
			{
				// Compilation failed

				GLint maxLength = 0;
				glGetShaderiv(_name, GL_INFO_LOG_LENGTH, &maxLength); // Get length of info log string

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(_name, maxLength, &maxLength, &infoLog[0]); // Get info log string

				// Log shader error
				VGLOG_ERROR("%s", &infoLog[0]);
			}
		}
	}

	if (!success)
		DeleteShader(); // Cleanup if compilation failed

	return success;
}

void Shader::DeleteShader()
{
	glDeleteShader(_name);
	_name = 0;
}

NS_VG_END
