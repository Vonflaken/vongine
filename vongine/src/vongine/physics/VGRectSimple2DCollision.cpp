#include "VGRectSimple2DCollision.h"
#include "base/VGTypes.h"
#include "rendering/VGVertexTypes.h"
#include "base/VGUtils.h"
#include "base/VGCoreManager.h"

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

void RectSimple2DCollision::DrawDebugShape(const float posZ, const float drawOrder) const
{
#if VG_DEBUG
	// Update position of vertices
	// Basically draw a quad	
	// Starts at bottom-left and continue counterclock-wise
	VERTEX_P3F vertices[] = {
		// 0 - bl		  // 1 - br					 // 2 - tr							  // 3 - tl
		{ _x, _y, posZ }, { _x + _width, _y, posZ }, { _x + _width, _y + _height, posZ }, { _x, _y + _height, posZ }
	};
	// Build indices - counterclock-wise
	uint32 indices[] = { 0, 1, 3, 1, 2, 3 };

	// Update draw command
	_debugDrawCmd->Update(glm::mat4(1.f), drawOrder, 0, _debugMat.get(), vertices, sizeof(vertices), indices, sizeof(indices));
	// Submit draw command
	CoreManager::GetInstance().GetRenderer()->AddRenderCommand(_debugDrawCmd.get(), RenderQueue::TRANSPARENT);
#endif // VG_DEBUG
}

NS_VG_END
