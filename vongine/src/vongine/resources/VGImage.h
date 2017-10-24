#ifndef __VGIMAGE_H__
#define __VGIMAGE_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "base/VGUtils.h"

#include <memory>
#include <string>

NS_VG_BEGIN

using namespace utils;

enum class InternalPixelFormat
{
	UNKNOWN,
	R8G8B8A8,	/// RGBA 8-bits per component
	R8G8B8,		/// RGB 8-bits per component
	G8A8,		/// Gray + Alpha 8-bits per component
	G8,			/// Gray 8-bits per component
	A8			/// Alpha 8-bits per component
};

class DLLAPI Image
{
public:
	Image();

	/**
	* Load a image file and populate properties
	*/
	bool InitWithFile(const std::string& filename);

	/**
	* Returns pointer to pixel array
	*/
	const unsigned char* GetPixelBuffer() const { return _pixels.get(); }

	/**
	* Getter init state
	*/
	bool IsInit() const { return _isInit; }
	/**
	* Getter of image's width
	*/
	uint32 GetWidth() const { return _width; }
	/**
	* Getter of image's height
	*/
	uint32 GetHeight() const { return _height; }

	/**
	* Getter internal pixel format of image
	*/
	InternalPixelFormat GetInternalPixelFormat() const { return _format; }
	/**
	* Getter GL pixel format of image
	*/
	int32 GetGLPixelFormat() const { return Image::GetGLValueFromInternal(_format); }

	/**
	* Getter color depth in bits of image
	*/
	uint32 GetBPP() const;

private:
	/**
	* Only 8-bits per components formats for now
	* @return An image format depends on number of components
	*/
	static InternalPixelFormat GetFormatFromNumComponents(const uint32 numComponents);
	/**
	* @return GL value matching the internal type or -1 if doesn't find a match
	*/
	static int32 GetGLValueFromInternal(const InternalPixelFormat format);

private:
	bool _isInit;

	std::unique_ptr<unsigned char, VG_Free_Deleter> _pixels;
	uint32 _width, _height;
	uint32 _numComponents;
	InternalPixelFormat _format;
};

NS_VG_END

#endif // __VGIMAGE_H__
