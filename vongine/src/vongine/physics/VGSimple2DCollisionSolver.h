#ifndef __VGSIMPLE2DCOLLISIONSOLVER_H__
#define __VGSIMPLE2DCOLLISIONSOLVER_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

class DLLAPI Simple2DCollisionSolver
{
public:
	static bool CircleToCircle(const float x1, const float y1, const uint32 r1, const float x2, const float y2, const uint32 r2);
	static bool CircleToRect(const float cx, const float cy, const uint32 cr, const float rx, const float ry, const uint32 rw, const uint32 rh);
	static bool RectToRect(const float x1, const float y1, const uint32 w1, const uint32 h1, const float x2, const float y2, const uint32 w2, const uint32 h2);
};

NS_VG_END

#endif // __VGSIMPLE2DCOLLISIONSOLVER_H__
