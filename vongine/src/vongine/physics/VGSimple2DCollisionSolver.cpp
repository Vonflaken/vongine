#include "VGSimple2DCollisionSolver.h"
#include "base/VGMathExtension.h"

#include "glm/glm.hpp"

NS_VG_BEGIN

using namespace glm;
using namespace mathex;

bool Simple2DCollisionSolver::CircleToCircle(const float x1, const float y1, const float r1, const float x2, const float y2, const float r2)
{
	float gap = distance(vec2(x1, y1), vec2(x2, y2));
	if (gap <= r1 + r2)
		return true;

	return false;
}

bool Simple2DCollisionSolver::CircleToRect(const float cx, const float cy, const float cr, const float rx, const float ry, const float rw, const float rh)
{
	float lookatx, lookaty;
	ClosestPointToRect(cx, cy, rx, ry, rw, rh, &lookatx, &lookaty);
	if (distance(vec2(cx, cy), vec2(lookatx, lookaty)) < cr)
		return true;

	return false;
}

bool Simple2DCollisionSolver::RectToRect(const float x1, const float y1, const float w1, const float h1, const float x2, const float y2, const float w2, const float h2)
{
	return RectsOverlap(x1, y1, w1, h1, x2, y2, w2, h2);
}

NS_VG_END
