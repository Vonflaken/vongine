#ifndef __VGCIRCLESIMPLE2DCOLLISION_H__
#define __VGCIRCLESIMPLE2DCOLLISION_H__

#include "VGMacros.h"
#include "physics/VGSimple2DCollision.h"
#include "physics/VGSimple2DCollisionSolver.h"

NS_VG_BEGIN

class DLLAPI CircleSimple2DCollision : public Simple2DCollision
{
public:
	CircleSimple2DCollision(const float x, const float y, const uint32 radius)
	{
		UpdateShape(x, y, radius);

		_type = Simple2DCollisionType::Circle;
	}

	inline bool DoesCollide(Simple2DCollision const * const other) const override { return other->DoesCollide(_x, _y, _radius); }
	inline bool DoesCollide(const float cx, const float cy, const uint32 cradius) const override { return Simple2DCollisionSolver::CircleToCircle(_x, _y, _radius, cx, cy, cradius); }
	inline bool DoesCollide(const float rx, const float ry, const uint32 rwidth, const uint32 rheight) const override { return Simple2DCollisionSolver::CircleToRect(_x, _y, _radius, rx, ry, rwidth, rheight); }

	void DrawDebugShape(const float posZ, const float drawOrder) const override;

	void UpdateShape(const float x, const float y, const uint32 radius) override;

private:
	float _x;
	float _y;
	uint32 _radius;
};

NS_VG_END

#endif // __VGCIRCLESIMPLE2DCOLLISION_H__
