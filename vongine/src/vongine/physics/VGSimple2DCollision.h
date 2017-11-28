#ifndef __VGSIMPLE2DCOLLISION_H__
#define __VGSIMPLE2DCOLLISION_H__

#include "VGMacros.h"

NS_VG_BEGIN

enum class Simple2DCollisionType
{
	None,
	Circle, 
	Rect
};

/**
* Position and other measure values of collision is in absolute screen coords.
* Understands that position is at center of the object.
*/
class DLLAPI Simple2DCollision
{
public:
	virtual inline bool DoesCollide(Simple2DCollision const * const other) const = 0;
	virtual inline bool DoesCollide(const float cx, const float cy, const float cradius) const = 0;
	virtual inline bool DoesCollide(const float rx, const float ry, const float rwidth, const float rheight) const = 0;

	virtual void UpdateShape(const float x, const float y, const float width, const float height) {};
	virtual void UpdateShape(const float x, const float y, const float radius) {};

	Simple2DCollisionType GetType() const { return _type; }

	/**
	* Draw with green lines the collision shape.
	* Use graphic lib fixed pipeline functions.
	*/
	virtual inline void DrawDebugShape() const = 0;

protected:
	Simple2DCollisionType _type;
};

NS_VG_END

#endif // __VGSIMPLE2DCOLLISION_H__
