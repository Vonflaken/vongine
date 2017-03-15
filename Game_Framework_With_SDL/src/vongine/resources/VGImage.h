#ifndef __VGIMAGE_H__
#define __VGIMAGE_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include <memory>
#include "base/VGUtils.h"

NS_VG_BEGIN

enum InternalPixelFormat
{
	UNKNOWN,
	// Consumable by OpenGL
	R8G8B8A8 = GL_RGBA,					// RGBA 8-bits per component
	R8G8B8 = GL_RGB,					// RGB 8-bits per component
	G8A8 = GL_LUMINANCE_ALPHA,			// Gray + Alpha 8-bits per component
	G8 = GL_LUMINANCE					// Gray 8-bits per component
};

class __declspec(dllexport) Image
{
public:
	Image();

	/// Load a image file and populate properties
	void InitWithFile(const char* filename);

	/// Returns pointer to pixel array
	const unsigned char* GetPixelBuffer() const { return _pixels.get(); }

	/// Getter of image's width
	const uint32 GetWidth() const { return _width; }
	/// Getter of image's height
	const uint32 GetHeight() const { return _height; }

	/// Getter of image's pixel format
	const InternalPixelFormat GetPixelFormat() const { return _format; }

private:
	/// Returns an image format depends on number of components
	/// Only 8-bits per components formats for now
	static const InternalPixelFormat GetFormatFromNumComponents(const uint32 numComponents);

private:
	bool _isInit;
	uint32 _width, _height;
	std::unique_ptr<unsigned char, VG_Free_Deleter> _pixels;
	uint32 _numComponents;
	InternalPixelFormat _format;
};

NS_VG_END

#endif // __VGIMAGE_H__
