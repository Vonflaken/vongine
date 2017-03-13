#ifndef __VGTEXTURE2D_H__
#define __VGTEXTURE2D_H__

#include "VGMacros.h"
#include "ogl/glew.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Wrapper types for OpenGL defines

#include "ogl/glew.h"

enum TextureFilter
{
	POINT = GL_NEAREST,
	BILINEAR = GL_LINEAR
};

enum TextureWrap
{
	REPEAT_X,
	REPEAT_Y,
	// Consumable by OpenGL
	REPEAT = GL_REPEAT,
	CLAMP = GL_CLAMP
};

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Texture2D class declaration

class Image;

class __declspec(dllexport) Texture2D
{
public:
	Texture2D();
	virtual ~Texture2D();

	/// Generate a texture 2D graphic resource and prepare it to use it
	/// Only supports RGBA images
	void InitWithImage(const const Image* image, const TextureFilter filter = TextureFilter::BILINEAR, const TextureWrap wrapping = TextureWrap::REPEAT);

	/// Bind texture to work with it
	/// Next changes in textures target will affect this texture
	void Bind();

private:
	GLuint _textureId;
};

NS_VG_END

#endif // __VGTEXTURE2D_H__

