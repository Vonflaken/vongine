#ifndef __VGImage_H__
#define __VGImage_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include <memory>
#include "base/VGUtils.h"

NS_VG_BEGIN

class __declspec(dllexport) Image
{
public:
	Image();

	void InitWithFile(const char* filename);

	const unsigned char* GetPixelBuffer() const { return *(_pixels.get()); }

private:
	bool _isInit;
	uint32 _width, _height;
	std::unique_ptr<unsigned char*, VG_Free_Deleter> _pixels;
	uint32 _numComponents;
};

NS_VG_END

#endif // __VGImage_H__
