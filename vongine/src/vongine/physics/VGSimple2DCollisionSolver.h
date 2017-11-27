#ifndef __VGSIMPLE2DCOLLISIONSOLVER_H__
#define __VGSIMPLE2DCOLLISIONSOLVER_H__

#include "VGMacros.h"

NS_VG_BEGIN

class DLLAPI Simple2DCollisionSolver
{
public:
	static bool CircleToCircle(const float x1, const float y1, const float r1, const float x2, const float y2, const float r2);
	static bool CircleToRect(const float cx, const float cy, const float cr, const float rx, const float ry, const float rw, const float rh);
	static bool RectToRect(const float x1, const float y1, const float w1, const float h1, const float x2, const float y2, const float w2, const float h2);
};

NS_VG_END

#endif // __VGSIMPLE2DCOLLISIONSOLVER_H__
