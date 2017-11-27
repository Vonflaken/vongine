#ifndef __VGMATHEXTENSION_H__
#define __VGMATHEXTENSION_H__

#include "VGMacros.h"

NS_VG_BEGIN

namespace mathex
{
	void ClosestPointToRect(const float x, const float y, const float rectx, const float recty, const float width, const float height, float* const outx, float* const outy);
	bool ValueInRange(const float value, const float min, const float max);
	bool RectsOverlap(const float x1, const float y1, const float width1, const float height1, const float x2, const float y2, const float width2, const float height2);
}

NS_VG_END

#endif // __VGMATHEXTENSION_H__
