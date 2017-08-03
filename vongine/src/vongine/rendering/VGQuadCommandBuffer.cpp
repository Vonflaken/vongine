#include "VGQuadCommandBuffer.h"

NS_VG_BEGIN

void QuadCommandBuffer::InitWithStride(const uint32 vertStride)
{
	CommandBuffer::Init();

	_indicesSize = sizeof(uint32) * 6;
	uint32* ptrIndices = (uint32*)malloc(_indicesSize); // Alloc mem for storing 6 indices
	// index 0 -> 0			index 1 -> 1			index 2 -> 3
	*ptrIndices = 0;		*(ptrIndices + 1) = 1;	*(ptrIndices + 2) = 3;
	// index 3 -> 1			index 4 -> 2			index 5 -> 3
	*(ptrIndices + 3) = 1;	*(ptrIndices + 4) = 2;	*(ptrIndices + 5) = 3;
	
	_indices.reset(ptrIndices); // Takes ownership of indices pointer

	glBindVertexArray(_VAO);
	// Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	// Copy indices to gfx mem
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize, _indices.get(), GL_STATIC_DRAW);

	_verticesSize = vertStride * 4;
	_vertices.reset((void*)malloc(_verticesSize)); // Alloc mem for 4 vertices
}

void QuadCommandBuffer::PrepareToDraw()
{
	if (!_isInit)
		return;

	// Bind buffers
	glBindVertexArray(_VAO);

	if (_verticesWasUpdated)
	{
		// Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		// Copy vertices to gfx mem
		glBufferData(GL_ARRAY_BUFFER, _verticesSize, _vertices.get(), GL_DYNAMIC_DRAW);
	}

	if (_material)
		_material->Use();

	_verticesWasUpdated = false;
}

NS_VG_END
