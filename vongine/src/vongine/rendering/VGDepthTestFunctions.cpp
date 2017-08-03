#include "VGDepthTestFunctions.h"

#include "ogl/glew.h"

NS_VG_BEGIN

namespace DepthTestFunctionsHelpers
{
	int32 GetGLValueFromInternal(const DepthTestFunction internalVal)
	{
		int32 glVal = -1;
		switch (internalVal)
		{
		case DepthTestFunction::ALWAYS:
			glVal = GL_ALWAYS;
			break;
		case DepthTestFunction::NEVER:
			glVal = GL_NEVER;
			break;
		case DepthTestFunction::LESS:
			glVal = GL_LESS;
			break;
		case DepthTestFunction::EQUAL:
			glVal = GL_EQUAL;
			break;
		case DepthTestFunction::LEQUAL:
			glVal = GL_LEQUAL;
			break;
		case DepthTestFunction::GREATER:
			glVal = GL_GREATER;
			break;
		case DepthTestFunction::NOTEQUAL:
			glVal = GL_NOTEQUAL;
			break;
		case DepthTestFunction::GEQUAL:
			glVal = GL_GEQUAL;
			break;
		}
		return glVal;
	}
}

NS_VG_END
