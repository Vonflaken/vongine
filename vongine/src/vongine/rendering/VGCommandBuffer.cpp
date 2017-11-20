#include "VGCommandBuffer.h"

#include "ogl/glew.h"

NS_VG_BEGIN

using namespace utils;

CommandBuffer::CommandBuffer()
: _isInit(false)
, _VBO(0)
, _VAO(0)
, _EBO(0)
, _verticesWasUpdated(false)
, _indicesWasUpdated(false)
, _vertices(nullptr, VG_Free_Deleter())
, _verticesSize(0)
, _indices(nullptr, VG_Free_Deleter())
, _indicesSize(0)
, _drawOrder(0.f)
, _modelViewMatrix()
, _material(nullptr)
{}

CommandBuffer::~CommandBuffer()
{
	// Free gfx buffers
	glDeleteBuffers(1, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_EBO);
}

void CommandBuffer::Init()
{
	if (_isInit)
		return;

	// Generate gfx buffers
	glGenBuffers(1, &_VBO);
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_EBO);

	_isInit = true;
}

void CommandBuffer::InitWithData(const void* tempVertBuff, const uint32 tempVertBuffSize, const uint32* tempIndicesBuff, const uint32 tempIndicesBuffSize)
{
	Init();

	// Alloc mem for buffers
	ResizeVertices(tempVertBuffSize);
	ResizeIndices(tempIndicesBuffSize);

	// Set data
	CopyVertices(tempVertBuff);
	CopyIndices(tempIndicesBuff);
}

void CommandBuffer::Update(
	const glm::mat4& modelViewMatrix, 
	const float drawOrder, 
	const uint32 flags, 
	Material* material, 
	const void* tempVertBuff, 
	const uint32 tempVertBuffSize, 
	const uint32* tempIndicesBuff, 
	const uint32 tempIndicesBuffSize)
{
	_modelViewMatrix = modelViewMatrix;
	_drawOrder = drawOrder;
	_material = material;

	if (tempVertBuffSize > 0 && tempVertBuffSize != _verticesSize)
	{ // Fit vertices buffer to new size
		ResizeVertices(tempVertBuffSize);
	}
	if (tempVertBuff && tempVertBuffSize == _verticesSize)
	{ // Use the new vertices buffer provided
		CopyVertices(tempVertBuff);
	}

	if (tempIndicesBuffSize > 0 && tempIndicesBuffSize != _indicesSize)
	{ // Fit indices buffer to new size
		ResizeIndices(tempIndicesBuffSize);
	}
	if (tempIndicesBuff && tempIndicesBuffSize == _indicesSize)
	{ // Use the new indices buffer provided
		CopyVertices(tempVertBuff);
	}
}

void CommandBuffer::PrepareToDraw()
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

	if (_indicesWasUpdated)
	{
		// Bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		// Copy indices to gfx mem
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize, _indices.get(), GL_DYNAMIC_DRAW);
	}

	if (_material)
		_material->Use();

	_verticesWasUpdated = _indicesWasUpdated = false;
}

void CommandBuffer::ResizeVertices(const uint32 tempVertBuffSize)
{
	_verticesSize = tempVertBuffSize;
	_vertices.reset((void*)malloc(tempVertBuffSize));
}

void CommandBuffer::ResizeIndices(const uint32 tempIndicesBuffSize)
{
	_indicesSize = tempIndicesBuffSize;
	_indices.reset((uint32*)malloc(tempIndicesBuffSize));
}

void CommandBuffer::CopyVertices(const void* tempVertBuff)
{
	memcpy(_vertices.get(), tempVertBuff, _verticesSize);
	_verticesWasUpdated = true;
}

void CommandBuffer::CopyIndices(const uint32* tempIndicesBuff)
{
	memcpy(_indices.get(), tempIndicesBuff, _indicesSize);
	_indicesWasUpdated = true;
}

NS_VG_END
