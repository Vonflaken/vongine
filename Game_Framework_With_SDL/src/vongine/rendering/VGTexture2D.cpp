#include "VGTexture2D.h"
#include "resources/VGImage.h"
#include "base/VGUtils.h"

NS_VG_BEGIN

Texture2D::Texture2D()
: _textureId(0)
{}

Texture2D::~Texture2D()
{
	// Free resource
	glDeleteTextures(1, &_textureId);
}

void Texture2D::InitWithImage(const const Image* image, const TextureFilter filter = TextureFilter::BILINEAR, const TextureWrap wrapping = TextureWrap::REPEAT)
{
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, setWrapX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, setWrapY);

	// Set filter parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	// Load image into texture
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		image->GetPixelFormat(), 
		image->GetWidth(), 
		image->GetHeight(), 
		0, 
		image->GetPixelFormat, 
		GL_UNSIGNED_BYTE, 
		image->GetPixelBuffer()); // TODO: Add more compatible image formats
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _textureId);
}

NS_VG_END
