#include "VGSimple2DCollisionSolver.h"
#include "base/VGMathExtension.h"

#include "glm/glm.hpp"

NS_VG_BEGIN

using namespace mathex;

bool Simple2DCollisionSolver::CircleToCircle(const float x1, const float y1, const uint32 r1, const float x2, const float y2, const uint32 r2)
{
	float gap = glm::distance(glm::vec2(x1, y1), glm::vec2(x2, y2));
	if (gap <= r1 + r2)
		return true;

	return false;
}

bool Simple2DCollisionSolver::CircleToRect(const float cx, const float cy, const uint32 cr, const float rx, const float ry, const uint32 rw, const uint32 rh)
{
	float lookatx, lookaty;
	ClosestPointToRect(cx, cy, rx, ry, (float)rw, (float)rh, &lookatx, &lookaty);
	if (glm::distance(glm::vec2(cx, cy), glm::vec2(lookatx, lookaty)) < cr)
		return true;

	return false;
}

bool Simple2DCollisionSolver::RectToRect(const float x1, const float y1, const uint32 w1, const uint32 h1, const float x2, const float y2, const uint32 w2, const uint32 h2)
{
	return RectsOverlap(x1, y1, (float)w1, (float)h1, x2, y2, (float)w2, (float)h2);
}

NS_VG_END
