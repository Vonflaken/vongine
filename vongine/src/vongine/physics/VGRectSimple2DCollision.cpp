#include "VGRectSimple2DCollision.h"
#include "base/VGTypes.h"

#include "ogl/glew.h"

NS_VG_BEGIN

void RectSimple2DCollision::UpdateShape(const float x, const float y, const float width, const float height) 
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
	glLineWidth(2.5);
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_LINES);
	// Draw rectangle with lines (two vertex (points) build a line)
	glVertex2f(_x, _y); // Bottom-left
	glVertex2f(_x + _width, _y); // Bottom-right
	glVertex2f(_x + _width, _y + _height); // Top-right
	glVertex2f(_x, _y + _height); // Top-left
	glEnd();
}

NS_VG_END
