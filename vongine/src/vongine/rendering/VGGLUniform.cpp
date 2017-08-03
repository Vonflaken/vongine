#include "VGGLUniform.h"

NS_VG_BEGIN

namespace GLUniformHelpers
{
	void SetValue(GLUniform* uniform, void const * value)
	{
		uint32 type = uniform->type;
		void* uniValue = uniform->GetValue();
		// Traverse each element of uniform buffer setting new value
		for (uint32 i = 0; i < uniform->length; i++)
		{
			// Cast to matching type for setting value at correct memory location
			if (type == GL_FLOAT)
			{
				*(((float*)uniValue) + i) = *(((float const *)value) + i);
			}
			else if (type == GL_INT)
			{
				*(((int32*)uniValue) + i) = *(((int32 const *)value) + i);
			}
			else if (type == GL_UNSIGNED_INT)
			{
				*(((uint32*)uniValue) + i) = *(((uint32 const *)value) + i);
			}
		}
	}
}

NS_VG_END
