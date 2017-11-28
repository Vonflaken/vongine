#ifndef __VGRECTSIMPLE2DCOLLISION_H__
#define __VGRECTSIMPLE2DCOLLISION_H__

#include "VGMacros.h"
#include "physics/VGSimple2DCollision.h"
#include "physics/VGSimple2DCollisionSolver.h"

NS_VG_BEGIN

class DLLAPI RectSimple2DCollision : public Simple2DCollision
{
public:
	RectSimple2DCollision(const float x, const float y, const float width, const float height)
	{
		UpdateShape(x, y, width, height); // Set pos and size

		_type = Simple2DCollisionType::Rect;
	}

	inline bool DoesCollide(Simple2DCollision const * const other) const override { return other->DoesCollide(_x, _y, _width, _height); }
	inline bool DoesCollide(const float cx, const float cy, const float cradius) const override { return Simple2DCollisionSolver::CircleToRect(cx, cy, cradius, _x, _y, _width, _height); }
	inline bool DoesCollide(const float rx, const float ry, const float rwidth, const float rheight) const override { return Simple2DCollisionSolver::RectToRect(_x, _y, _width, _height, rx, ry, rwidth, rheight); }

	void DrawDebugShape() const override;

	void UpdateShape(const float x, const float y, const float width, const float height) override;

private:
	float _x;
	float _y;
	float _width;
	float _height;
};

NS_VG_END

#endif // __VGRECTSIMPLE2DCOLLISION_H__
