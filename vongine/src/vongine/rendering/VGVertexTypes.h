#ifndef __VGVERTEXTYPES_H__
#define __VGVERTEXTYPES_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

struct VERTEX_P3F_C4F_T2F
{
	float position[3];
	float color[4];
	float uv[2];
};

NS_VG_END

#endif // __VGVERTEXTYPES_H__
