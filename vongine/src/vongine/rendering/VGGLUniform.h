#ifndef __VGGLUNIFORM_H__
#define __VGGLUNIFORM_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include "ogl/glew.h"

#include <string>

NS_VG_BEGIN

/*************************************************************** Types */

typedef struct {
	virtual void* GetValue() { return nullptr; }

	std::string name; /// Var name in shader
	uint32 type;
	uint32 length; /// Number of elements in array
} GLUniform;

struct GLUniform1f : public GLUniform {
	GLUniform1f() { type = GL_FLOAT; length = 1; }

	void* GetValue() override { return &value; }

	float value;
};

struct GLUniform1i : public GLUniform {
	GLUniform1i() { type = GL_INT; length = 1; }

	void* GetValue() override { return &value; }

	int32 value;
};

struct GLUniform1ui : public GLUniform {
	GLUniform1ui() { type = GL_UNSIGNED_INT; length = 1; }

	void* GetValue() override { return &value; }

	uint32 value;
};

struct GLUniform2f : public GLUniform {
	GLUniform2f() { type = GL_FLOAT; length = 2; }

	void* GetValue() override { return value; }

	float value[2];
};

struct GLUniform2i : public GLUniform {
	GLUniform2i() { type = GL_INT; length = 2; }

	void* GetValue() override { return value; }

	int32 value[2];
};

struct GLUniform2ui : public GLUniform {
	GLUniform2ui() { type = GL_UNSIGNED_INT; length = 2; }

	void* GetValue() override { return value; }

	uint32 value[2];
};

struct GLUniform3f : public GLUniform {
	GLUniform3f() { type = GL_FLOAT; length = 3; }

	void* GetValue() override { return value; }

	float value[3];
};

struct GLUniform3i : public GLUniform {
	GLUniform3i() { type = GL_INT; length = 3; }

	void* GetValue() override { return value; }

	int32 value[3];
};

struct GLUniform3ui : public GLUniform {
	GLUniform3ui() { type = GL_UNSIGNED_INT; length = 3; }

	void* GetValue() override { return value; }

	uint32 value[3];
};

struct GLUniform4f : public GLUniform {
	GLUniform4f() { type = GL_FLOAT; length = 4; }

	void* GetValue() override { return value; }

	float value[4];
};

struct GLUniform4i : public GLUniform {
	GLUniform4i() { type = GL_INT; length = 4; }

	void* GetValue() override { return value; }

	int32 value[4];
};

struct GLUniform4ui : public GLUniform {
	GLUniform4ui() { type = GL_UNSIGNED_INT; length = 4; }

	void* GetValue() override { return value; }

	uint32 value[4];
};

struct GLUniformMatrix4f /* 4x4 */ : public GLUniform {
	GLUniformMatrix4f() { type = GL_FLOAT; length = 16; }

	void* GetValue() override { return value; }

	float value[16];
};
/*************************************************************** End types */


/*************************************************************** Functions */

namespace GLUniformHelpers
{
	void SetValue(GLUniform* uniform, void const * value);
}
/*************************************************************** End functions */
NS_VG_END

#endif // __VGGLUNIFORM_H__
