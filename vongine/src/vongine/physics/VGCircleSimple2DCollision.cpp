#include "VGCircleSimple2DCollision.h"
#include "base/VGTypes.h"
#include "rendering/VGVertexTypes.h"
#include "base/VGUtils.h"
#include "base/VGCoreManager.h"

NS_VG_BEGIN

void CircleSimple2DCollision::UpdateShape(const float x, const float y, const uint32 radius)
{ 
	_x = x; 
	_y = y; 
	_radius = radius; 
}

void CircleSimple2DCollision::DrawDebugShape(const float posZ, const float drawOrder) const
{
#if VG_DEBUG
	// Update position of vertices
	uint32 steps = 20; // Number of iterations for building the circle mesh
	uint32 verticesSize = (steps/*edges*/ + 1/*center*/) * sizeof(VERTEX_P3F);
	auto vertices = std::unique_ptr<VERTEX_P3F, utils::VG_Free_Deleter>((VERTEX_P3F*)malloc(verticesSize)); // Alloc mem for vertices
	uint32 indicesSize = steps * 3 * sizeof(uint32);
	auto indices = std::unique_ptr<uint32, utils::VG_Free_Deleter>((uint32*)malloc(indicesSize)); // Alloc mem for indices
	uint32* indicesPtr = indices.get();
	VERTEX_P3F* verticesPtr = vertices.get();
	verticesPtr[0] = { _x, _y, posZ }; // Set vertice of the center at first
	for (uint32 i = 1; i <= steps; i++) // Set vertices of circunference
	{
		double radians = glm::radians((i - 1) * (360.f / (float)steps)); // Get next angle
		float cos = glm::cos(radians);
		float sin = glm::sin(radians);
		verticesPtr[i] = { _x + cos * _radius, _y + sin * _radius, posZ }; // Set vertice

		// Set indices
		indicesPtr[(i - 1) * 3] = 0;
		indicesPtr[(i - 1) * 3 + 1] = i;
		indicesPtr[(i - 1) * 3 + 2] = (i == steps) ? 1 : i + 1; // The last triangle encloses the circle mesh, so last indice must points to second vertice
	}

	// Update draw command
	_debugDrawCmd->Update(glm::mat4(1.f), drawOrder, 0, _debugMat.get(), verticesPtr, verticesSize, indicesPtr, indicesSize);
	// Submit draw command
	CoreManager::GetInstance().GetRenderer()->AddRenderCommand(_debugDrawCmd.get(), RenderQueue::TRANSPARENT);
#endif // VG_DEBUG
}

NS_VG_END
