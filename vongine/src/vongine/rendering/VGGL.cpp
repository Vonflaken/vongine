#include "VGGL.h"
#include "base/VGLogger.h"

NS_VG_BEGIN

namespace GL
{
	std::string GetErrorDesc()
	{
		GLenum err = glGetError();
		std::string errDesc;
		switch (err)
		{
		case GL_NO_ERROR:
			errDesc = "";
			break;
		case GL_INVALID_ENUM:
			errDesc = "GL_INVALID_ENUM - Given when an enumeration parameter is not a legal enumeration for that function. This is given only for local problems; if the spec allows the enumeration in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead.";
			break;
		case GL_INVALID_VALUE:
			errDesc = "GL_INVALID_VALUE - Given when a value parameter is not a legal value for that function. This is only given for local problems; if the spec allows the value in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead.";
			break;
		case GL_INVALID_OPERATION:
			errDesc = "GL_INVALID_OPERATION - Given when the set of state for a command is not legal for the parameters given to that command. It is also given for commands where combinations of parameters define what the legal parameters are.";
			break;
		case GL_STACK_OVERFLOW:
			errDesc = "GL_STACK_OVERFLOW - Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size.";
			break;
		case GL_STACK_UNDERFLOW:
			errDesc = "GL_STACK_UNDERFLOW - Given when a stack popping operation cannot be done because the stack is already at its lowest point.";
			break;
		case GL_OUT_OF_MEMORY:
			errDesc = "GL_OUT_OF_MEMORY - Given when performing an operation that can allocate memory, and the memory cannot be allocated. The results of OpenGL functions that return this error are undefined; it is allowable for partial operations to happen.";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errDesc = "GL_INVALID_FRAMEBUFFER_OPERATION - Given when doing anything that would attempt to read from or write/render to a framebuffer that is not complete.";
			break;
		case GL_CONTEXT_LOST:
			errDesc = "GL_CONTEXT_LOST - Given if the OpenGL context has been lost, due to a graphics card reset.";
			break;
		default:
			errDesc = "Error code not found.";
			break;
		}
		return errDesc;
	}
}

NS_VG_END
