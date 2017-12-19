#ifndef __VGSIMPLE2DCOLLISION_H__
#define __VGSIMPLE2DCOLLISION_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "rendering/VGWireframeMaterial.h"
#include "rendering/VGCommandBuffer.h"

#include <memory>

NS_VG_BEGIN

enum class Simple2DCollisionType
{
	None,
	Circle, 
	Rect
};

class WireframeMaterial;
class CommandBuffer;

/**
* Position and other measure values of collision is in absolute screen coords.
* Understands that position is at center of the object.
*/
class DLLAPI Simple2DCollision
{
public:
	Simple2DCollision();

	virtual inline bool DoesCollide(Simple2DCollision const * const other) const = 0;
	virtual inline bool DoesCollide(const float cx, const float cy, const uint32 cradius) const = 0;
	virtual inline bool DoesCollide(const float rx, const float ry, const uint32 rwidth, const uint32 rheight) const = 0;

	virtual void UpdateShape(const float x, const float y, const uint32 width, const uint32 height) {};
	virtual void UpdateShape(const float x, const float y, const uint32 radius) {};

	Simple2DCollisionType GetType() const { return _type; }

	/**
	* Draw with green lines the collision shape.
	* Use graphic lib fixed pipeline functions.
	*/
	virtual void DrawDebugShape(const float posZ, const float drawOrder) const = 0;

protected:
	Simple2DCollisionType _type;
	std::unique_ptr<WireframeMaterial> _debugMat;
	std::unique_ptr<CommandBuffer> _debugDrawCmd;
};

NS_VG_END

#endif // __VGSIMPLE2DCOLLISION_H__
