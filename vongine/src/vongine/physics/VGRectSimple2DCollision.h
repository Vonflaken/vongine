#ifndef __VGRECTSIMPLE2DCOLLISION_H__
#define __VGRECTSIMPLE2DCOLLISION_H__

#include "VGMacros.h"
#include "physics/VGSimple2DCollision.h"
#include "physics/VGSimple2DCollisionSolver.h"

NS_VG_BEGIN

class DLLAPI RectSimple2DCollision : public Simple2DCollision
{
public:
	RectSimple2DCollision(const float x, const float y, const uint32 width, const uint32 height)
	{
		UpdateShape(x, y, width, height); // Set pos and size

		_type = Simple2DCollisionType::Rect;
	}

	inline bool DoesCollide(Simple2DCollision const * const other) const override { return other->DoesCollide(_x, _y, _width, _height); }
	inline bool DoesCollide(const float cx, const float cy, const uint32 cradius) const override { return Simple2DCollisionSolver::CircleToRect(cx, cy, cradius, _x, _y, _width, _height); }
	inline bool DoesCollide(const float rx, const float ry, const uint32 rwidth, const uint32 rheight) const override { return Simple2DCollisionSolver::RectToRect(_x, _y, _width, _height, rx, ry, rwidth, rheight); }

	void DrawDebugShape(const float posZ, const float drawOrder) const override;

	void UpdateShape(const float x, const float y, const uint32 width, const uint32 height) override;

private:
	float _x; // Left bound
	float _y; // Bottom bound
	uint32 _width;
	uint32 _height;
};

NS_VG_END

#endif // __VGRECTSIMPLE2DCOLLISION_H__
