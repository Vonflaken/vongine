#include "VGGLProgramState.h"

#include "ogl/glew.h"

NS_VG_BEGIN

GLProgramState::GLProgramState()
: _stride(0)
, _programID(0)
, _isInit(false)
{}

void GLProgramState::Init(const uint32 stride, const GLuint programID)
{
	_stride = stride;
	_programID = programID;

	_isInit = true;
}

void GLProgramState::SetAttribFloat(const uint32 attribLocation, const uint32 length, const uint32 offset)
{
	SetAttrib(GL_FLOAT, attribLocation, length, offset);
}

void GLProgramState::SetAttrib(const uint32 type, const uint32 attribLocation, const uint32 length, const uint32 offset)
{
	// Create temporal config object
	AttribCfg cfg;
	cfg.type = type;
	cfg.attribLocation = attribLocation;
	cfg.length = length;
	cfg.offset = offset;

	_tempAttribsCfg.push_back(cfg);
}

// FIXME: ProgramState needs to be unique for each draw command
// Vertex attribs definition is the trigger
// It's bit hackish as is now
void GLProgramState::ApplyAttr()
{
	if (!_isInit) // Set the stride is required
		return;

	int32 isBound = 0;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &isBound);

	if (isBound)
	{
		for (uint32 i = 0; i < _tempAttribsCfg.size(); i++)
		{
			AttribCfg& cfg = _tempAttribsCfg[i];
			glVertexAttribPointer(cfg.attribLocation, cfg.length, cfg.type, GL_FALSE, _stride, (void*)cfg.offset);
			glEnableVertexAttribArray(cfg.attribLocation);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO

	// Clean up temporal array
	//_tempAttribsCfg.clear();
}

void GLProgramState::ApplyUni(const std::vector<std::unique_ptr<GLUniform>>& uniforms)
{
	for (uint32 i = 0; i < uniforms.size(); i++)
	{
		ApplyUni(uniforms[i].get());
	}
}

void GLProgramState::ApplyUni(GLUniform* uniform)
{
	int32 location = glGetUniformLocation(_programID, uniform->name.c_str());
	// If location is equal to '-1' means uniform wasn't found 
	// because of either incorrect name or optimized-away 
	// (compiler discard uniforms if are not used in shader code)
	if (location >= 0)
	{
		// Find type of the data then find number the elements in order to use proper 
		// glUniformX function
		uint32 length = uniform->length;
		if (uniform->type == GL_FLOAT)
		{
			float* values = (float*)uniform->GetValue();
			if (length == 1)
				glUniform1f(location, *values);
			else if (length == 2)
				glUniform2fv(location, 1, values);
			else if (length == 3)
				glUniform3fv(location, 1, values);
			else if (length == 4)
				glUniform4fv(location, 1, values);
			else if (length == 16)
				glUniformMatrix4fv(location, 1, false, values);
		}
		else if (uniform->type == GL_INT)
		{
			int32* values = (int32*)uniform->GetValue();
			if (length == 1)
				glUniform1i(location, *values);
			else if (length == 2)
				glUniform2iv(location, 1, values);
			else if (length == 3)
				glUniform3iv(location, 1, values);
			else if (length == 4)
				glUniform4iv(location, 1, values);
		}
		else if (uniform->type == GL_UNSIGNED_INT)
		{
			uint32* values = (uint32*)uniform->GetValue();
			if (length == 1)
				glUniform1ui(location, *values);
			else if (length == 2)
				glUniform2uiv(location, 1, values);
			else if (length == 3)
				glUniform3uiv(location, 1, values);
			else if (length == 4)
				glUniform4uiv(location, 1, values);
		}
	}
}

NS_VG_END
