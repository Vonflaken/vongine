#include "VGCircleSimple2DCollision.h"
#include "base/VGTypes.h"

#include "ogl/glew.h"
#include "glm/glm.hpp"

NS_VG_BEGIN

void CircleSimple2DCollision::UpdateShape(const float x, const float y, const uint32 radius)
{ 
	_x = x; 
	_y = y; 
	_radius = radius; 
}

void CircleSimple2DCollision::DrawDebugShape() const
{

}

NS_VG_END
