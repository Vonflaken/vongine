#ifndef __VGImage_H__
#define __VGImage_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

class __declspec(dllexport) Image
{
private:
	uint32 width, height;
	unsigned char* data; // Pixels buffer
};

NS_VG_END

#endif // __VGImage_H__
