#include "VGRenderContext.h"
#include "ogl/glew.h"

NS_VG_BEGIN

const uint16 RenderContext::GetGLTextureUnitValue(const uint8 unitNumber)
{
	uint16 rvalue = GL_TEXTURE0; // Default value, returns whereas unitNumber is invalid or out of range
	switch (unitNumber)
	{
	case 1: { rvalue = GL_TEXTURE1; break; } case 2: { rvalue = GL_TEXTURE2; break; } case 3: { rvalue = GL_TEXTURE3; break; } case 4: { rvalue = GL_TEXTURE4; break; } case 5: { rvalue = GL_TEXTURE5; break; }
	case 6: { rvalue = GL_TEXTURE6; break; } case 7: { rvalue = GL_TEXTURE7; break; } case 8: { rvalue = GL_TEXTURE8; break; } case 9: { rvalue = GL_TEXTURE9; break; } case 10: { rvalue = GL_TEXTURE10; break; }
	case 11: { rvalue = GL_TEXTURE11; break; } case 12: { rvalue = GL_TEXTURE12; break; } case 13: { rvalue = GL_TEXTURE13; break; } case 14: { rvalue = GL_TEXTURE14; break; } case 15: { rvalue = GL_TEXTURE15; break; }
	default: break;
	}

	return rvalue;
}

void RenderContext::ActiveTextureUnit(const uint8 unitNumber)
{
	const uint16 texUnitVal = RenderContext::GetGLTextureUnitValue(unitNumber);
	glActiveTexture(texUnitVal);
}

NS_VG_END
