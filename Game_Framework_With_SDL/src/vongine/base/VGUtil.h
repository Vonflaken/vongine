#ifndef __VGUtil_H__
#define __VGUtil_H__

#include "VGMacros.h"
#include <stdlib.h>

NS_VG_BEGIN

struct __declspec(dllexport) VG_Free_Deleter
{
public:
	inline void operator()(void* mem) const { free(mem); }
};

NS_VG_END

#endif // __VGUtil_H__
