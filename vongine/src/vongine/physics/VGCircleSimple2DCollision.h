#ifndef __VGCIRCLESIMPLE2DCOLLISION_H__
#define __VGCIRCLESIMPLE2DCOLLISION_H__

#include "VGMacros.h"
#include "physics/VGSimple2DCollision.h"
#include "physics/VGSimple2DCollisionSolver.h"

NS_VG_BEGIN

class DLLAPI CircleSimple2DCollision : public Simple2DCollision
{
public:
	CircleSimple2DCollision(const float x, const float y, const float radius)
	: _x(x)
	, _y(y)
	, _radius(radius)
	{
		_type = Simple2DCollisionType::Circle;
	}

	inline bool DoesCollide(Simple2DCollision const * const other) const override { return other->DoesCollide(_x, _y, _radius); }
	inline bool DoesCollide(const float cx, const float cy, const float cradius) const override { return Simple2DCollisionSolver::CircleToCircle(_x, _y, _radius, cx, cy, cradius); }
	inline bool DoesCollide(const float rx, const float ry, const float rwidth, const float rheight) const override { return Simple2DCollisionSolver::CircleToRect(_x, _y, _radius, rx, ry, rwidth, rheight); }

	inline void DrawDebugShape() const override;

	void UpdateShape(const float x, const float y, const float radius) override;

private:
	float _x;
	float _y;
	float _radius;
};

NS_VG_END

#endif // __VGCIRCLESIMPLE2DCOLLISION_H__
