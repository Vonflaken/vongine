#ifndef __VGUtils_H__
#define __VGUtils_H__

#include "VGMacros.h"
#include <stdlib.h>

NS_VG_BEGIN

struct __declspec(dllexport) VG_Free_Deleter
{
public:
	inline void operator()(void* mem) const { free(mem); }
};

NS_VG_END

#endif // __VGUtils_H__
