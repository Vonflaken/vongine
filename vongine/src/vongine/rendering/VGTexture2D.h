#ifndef __VGTEXTURE2D_H__
#define __VGTEXTURE2D_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

/************************************************* Wrapper types for GL constants */

enum class TextureFilter
{
	POINT,
	BILINEAR
};

enum class TextureWrap
{
	REPEAT_X,
	REPEAT_Y,
	REPEAT,
	CLAMP
};
/************************************************* End wrapper types for GL constants */


/************************************************* Texture2D class declaration */

class Image;

class DLLAPI Texture2D
{
public:
	Texture2D();
	virtual ~Texture2D();

	/**
	* Generate a texture 2D graphic resource and prepare it to use it
	* Only supports RGBA images
	*/
	bool InitWithImage(const Image* image, const TextureFilter filter = TextureFilter::BILINEAR, const TextureWrap wrapping = TextureWrap::REPEAT);

	/**
	* Bind texture to work with it
	* Next changes in textures target will affect this texture
	*/
	void Bind();
	/**
	* Bind texture to given texture unit
	*/
	void BindToTexUnit(const uint8 texUnit);

	uint32 GetWidth() const { return _width; }
	uint32 GetHeight() const { return _height; }

	bool IsInit() const { return _textureId != 0; }

private:
	/**
	* @return GL value matching the internal type or -1 if doesn't find a match
	*/
	int32 GetGLValueFromInternal(const TextureFilter internalVal) const;
	/**
	* @return GL value matching the internal type or -1 if doesn't find a match
	*/
	int32 GetGLValueFromInternal(const TextureWrap internalVal) const;

private:
	uint32 _textureId;

	uint32 _width, _height;
};
/************************************************* End Texture2D class declaration */

NS_VG_END

#endif // __VGTEXTURE2D_H__

