#include "VGBlendingFunctions.h"

#include "ogl/glew.h"

NS_VG_BEGIN

namespace BlendingFunctionsHelpers
{
	int32 GetGLValueFromInternal(const BlendFactor internalVal)
	{
		int32 glVal = -1;
		switch (internalVal)
		{
		case BlendFactor::ZERO:
			glVal = GL_ZERO;
			break;
		case BlendFactor::ONE:
			glVal = GL_ONE;
			break;
		case BlendFactor::SRC_COLOR:
			glVal = GL_SRC_COLOR;
			break;
		case BlendFactor::ONE_MINUS_SRC_COLOR:
			glVal = GL_ONE_MINUS_SRC_COLOR;
			break;
		case BlendFactor::DST_COLOR:
			glVal = GL_DST_COLOR;
			break;
		case BlendFactor::ONE_MINUS_DST_COLOR:
			glVal = GL_ONE_MINUS_DST_COLOR;
			break;
		case BlendFactor::SRC_ALPHA:
			glVal = GL_SRC_ALPHA;
			break;
		case BlendFactor::ONE_MINUS_SRC_ALPHA:
			glVal = GL_ONE_MINUS_SRC_ALPHA;
			break;
		case BlendFactor::DST_ALPHA:
			glVal = GL_DST_ALPHA;
			break;
		case BlendFactor::ONE_MINUS_DST_ALPHA:
			glVal = GL_ONE_MINUS_DST_ALPHA;
			break;
		}
		return glVal;
	}
}

NS_VG_END
