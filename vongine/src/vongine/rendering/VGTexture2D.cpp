#include "VGTexture2D.h"
#include "resources/VGImage.h"
#include "base/VGUtils.h"
#include "base/VGCoreManager.h"
#include "VGRenderContext.h"

#include "ogl/glew.h"

NS_VG_BEGIN

Texture2D::Texture2D()
: _textureId(0)
, _width(0)
, _height(0)
{}

Texture2D::~Texture2D()
{
	// Free resource
	glDeleteTextures(1, &_textureId);
}

bool Texture2D::InitWithImage(const Image* image, const TextureFilter filter, const TextureWrap wrapping)
{
	if (!image || !image->IsInit()) // Early exist if image is invalid or is not initialiced
		return false;

	// Generate resource
	glGenTextures(1, &_textureId);
	// Bind texture in order to work with it
	Bind();

	// Set wrap parameters
	// Set x-wrapping to REPEAT if wrapping param is REPEAT or REPEAT_X else set CLAMP
	TextureWrap setWrapX = (one_of(wrapping, TextureWrap::REPEAT, TextureWrap::REPEAT_X)) ? TextureWrap::REPEAT : TextureWrap::CLAMP;
	// Set y-wrapping to REPEAT if wrapping param is REPEAT or REPEAT_Y else set CLAMP
	TextureWrap setWrapY = (one_of(wrapping, TextureWrap::REPEAT, TextureWrap::REPEAT_Y)) ? TextureWrap::REPEAT : TextureWrap::CLAMP;
	// Apply wrap setting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLValueFromInternal(setWrapX));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLValueFromInternal(setWrapY));

	// Set filter parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLValueFromInternal(filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetGLValueFromInternal(filter));

	uint32 width = image->GetWidth();
	uint32 height = image->GetHeight();

	// Load image into texture
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		image->GetGLPixelFormat(), 
		width, 
		height, 
		0, 
		image->GetGLPixelFormat(), 
		GL_UNSIGNED_BYTE, 
		image->GetPixelBuffer());

	_width = width;
	_height = height;

	// TODO: I should add some error checking here in order to check if texture was generated correctly

	return true;
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _textureId);
}

void Texture2D::BindToTexUnit(const uint8 texUnit)
{
	CoreManager::GetInstance().RenderContext()->ActiveTextureUnit(texUnit);
	Bind();
}

int32 Texture2D::GetGLValueFromInternal(const TextureFilter internalVal) const
{
	int32 glVal = -1;
	switch (internalVal)
	{
	case TextureFilter::POINT:
		glVal = GL_NEAREST;
		break;
	case TextureFilter::BILINEAR:
		glVal = GL_LINEAR;
		break;
	}
	return glVal;
}

int32 Texture2D::GetGLValueFromInternal(const TextureWrap internalVal) const
{
	int32 glVal = -1;
	switch (internalVal)
	{
	case TextureWrap::REPEAT:
		glVal = GL_REPEAT;
		break;
	case TextureWrap::CLAMP:
		glVal = GL_CLAMP;
		break;
	}
	return glVal;
}

NS_VG_END
