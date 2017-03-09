#ifndef __VGIMAGE_H__
#define __VGIMAGE_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include <memory>
#include "base/VGUtils.h"

NS_VG_BEGIN

class __declspec(dllexport) Image
{
public:
	Image();

	/// Load a image file and populate properties
	void InitWithFile(const char* filename);

	/// Returns pointer to pixel array
	const unsigned char* GetPixelBuffer() const { return *(_pixels.get()); }

	/// Getter of image's width
	const uint32 GetWidth() const { return _width; }
	/// Getter of image's height
	const uint32 GetHeight() const { return _height; }

private:
	/// Returns an image format depends on number of components
	/// Only 8-bits per components formats for now
	static InternalImageFormat GetFormatFromNumComponents(const uint32 numComponents);

private:
	bool _isInit;
	uint32 _width, _height;
	std::unique_ptr<unsigned char*, VG_Free_Deleter> _pixels;
	uint32 _numComponents;
	InternalImageFormat _format;
};

NS_VG_END

#endif // __VGIMAGE_H__
