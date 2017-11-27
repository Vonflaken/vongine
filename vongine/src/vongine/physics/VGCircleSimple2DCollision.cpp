#include "VGCircleSimple2DCollision.h"
#include "base/VGTypes.h"

#include "ogl/glew.h"
#include "glm/glm.hpp"

NS_VG_BEGIN

void CircleSimple2DCollision::UpdateShape(const float x, const float y, const float radius) 
{ 
	_x = x; 
	_y = y; 
	_radius = radius; 
}

inline void CircleSimple2DCollision::DrawDebugShape() const
{
	glLineWidth(2.5);
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_LINES);
	// Draw circle with lines (two vertex (points) build a line)
	for (uint32 i = 0; i <= 360; i += 5)
	{
		float cos = glm::cos((float)i);
		float sin = glm::sin((float)i);
		glVertex2f(_x + _radius * cos, _y + _radius * sin);
	}
	glEnd();
}

NS_VG_END
