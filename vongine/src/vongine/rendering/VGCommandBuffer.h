#ifndef __VGCOMMANDBUFFER_H__
#define __VGCOMMANDBUFFER_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "base/VGUtils.h"
#include "VGMaterial.h"

#include "glm/glm.hpp"

#include <memory>

NS_VG_BEGIN

class DLLAPI CommandBuffer
{
public:
	CommandBuffer();
	virtual ~CommandBuffer();

	void Init();
	void InitWithData(const void* tempVertBuff, const uint32 tempVertBuffSize, const uint32* tempIndicesBuff, const uint32 tempIndicesBuffSize);

	bool IsInit() const { return _isInit; }

	/**
	* @param tempVertBuff Memcopyied to member var buffer.
	* @param tempIndicesBuff Memcopyied to member var buffer.
	*/
	virtual void Update(
		const glm::mat4& modelViewMatrix, 
		const float drawOrder, 
		const uint32 flags, 
		Material* material, 
		const void* tempVertBuff = nullptr, 
		const uint32 tempVertBuffSize = 0, 
		const uint32* tempIndicesBuff = nullptr, 
		const uint32 tempIndicesBuffSize = 0);
	/**
	* Bind gfx buffers.
	* Copy data to gfx buffers is were updated.
	* Use material.
	*/
	virtual void PrepareToDraw();
	/**
	* It's called after this command has been drawn, intented to undo changes to the render context that this drawcall may did.
	*/
	virtual void AfterDraw() {}

	uint32 GetIndicesLength() const { return _indicesSize / sizeof(uint32); }

	const Material* GetConstMaterial() const { return _material; }
	Material* GetMaterial() { return _material; }

	float GetDrawOrder() const { return _drawOrder; }
	const glm::mat4& GetMVMatrix() const { return _modelViewMatrix; }

protected:
	void ResizeVertices(const uint32 tempVertBuffSize);
	void ResizeIndices(const uint32 tempIndicesBuffSize);

	/**
	* @param tempVertBuff Copy _verticesSize num of bytes from buffer.
	*/
	void CopyVertices(const void* tempVertBuff);
	/**
	* @param tempIndicesBuff Copy _indicesSize num of bytes from buffer.
	*/
	void CopyIndices(const uint32* tempIndicesBuff);

protected:
	bool _isInit;

	// Graphic buffers
	uint32 _VAO;
	uint32 _VBO;
	uint32 _EBO;

	bool _verticesWasUpdated;
	bool _indicesWasUpdated;

	std::unique_ptr<void, utils::VG_Free_Deleter> _vertices;
	uint32 _verticesSize;
	std::unique_ptr<uint32, utils::VG_Free_Deleter> _indices;
	uint32 _indicesSize;

	float _drawOrder;
	glm::mat4 _modelViewMatrix;
	Material* _material;
};

NS_VG_END

#endif // __VGCOMMANDBUFFER_H__
