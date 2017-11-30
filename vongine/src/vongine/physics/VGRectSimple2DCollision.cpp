#include "VGRectSimple2DCollision.h"
#include "base/VGTypes.h"

#include "ogl/glew.h"

NS_VG_BEGIN

void RectSimple2DCollision::UpdateShape(const float x, const float y, const uint32 width, const uint32 height)
{ 
	// Take x, y as centered in the object so offset the position
	// to wrap from the center.
	_x = x - width / 2.f; 
	_y = y - height / 2.f; 
	_width = width; 
	_height = height; 
}

void RectSimple2DCollision::DrawDebugShape() const
{

}

NS_VG_END
