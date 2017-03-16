#include "VGShader.h"
#include "platform/VGFileUtils.h"
#include <vector>
#include "base/VGLogger.h"

NS_VG_BEGIN

Shader::Shader()
: _name(0)
{}

Shader::~Shader()
{
	// Shader deletion is deferred until shader is no longer attached to any program object
	glDeleteShader(_name);
}

/// Creates shader object of type required and compile it
/// Shader source from filename
void Shader::Compile(const char* filename, const ShaderType type)
{
	if (_name) // Don't continue if shader is already created
		return;

	// Create empty shader object
	_name = glCreateShader(type);
	
	// Read shader file
	File shaderFile(filename, "rb");
	uint32 totalBytesRead = shaderFile.Read();
	if (totalBytesRead > 0) // Check read is correct
	{
		const char* shaderText = shaderFile.GetBuffer();

		const GLint len = shaderFile.GetSize(); // WARNING: Unsafe cast from unsigned to signed
		// Feed shader with shader text
		glShaderSource(_name, 1, &shaderText, &len);

		// Compile shader
		glCompileShader(_name);

		// Handle compilation error
		GLint isCompiled = 0;
		glGetShaderiv(_name, GL_COMPILE_STATUS, &isCompiled); // Get compilation state
		if (isCompiled == GL_FALSE)
		{
			// Compilation failed

			GLint maxLength = 0;
			glGetShaderiv(_name, GL_INFO_LOG_LENGTH, &maxLength); // Get length of info log string

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(_name, maxLength, &maxLength, &infoLog[0]); // Get info log string

			// Log shader error
			VGLOG("%s", &infoLog[0]);
		}
	}
}

NS_VG_END
