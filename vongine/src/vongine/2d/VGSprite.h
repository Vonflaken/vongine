#ifndef __VGSPRITE_H__
#define __VGSPRITE_H__

#include "VGMacros.h"
#include "base/VGEntity.h"
#include "rendering/VGMaterialProtocol.h"
#include "rendering/VGQuadCommandBuffer.h"

NS_VG_BEGIN

class DLLAPI Sprite : public Entity, public MaterialProtocol
{
public:
	/** 
	* @param filename Name of image file.
	*/
	static std::shared_ptr<Sprite> Create(const std::string& filename);
	static std::shared_ptr<Sprite> Create(const std::string& filename, const glm::vec3& position);
	static std::shared_ptr<Sprite> Create(const std::string& filename, const glm::vec3& position, const uint32 width, const uint32 height);

	Sprite();

	bool Init(const std::string& filename, const glm::vec3& position, const uint32 width = 0, const uint32 height = 0);

	virtual void Draw(const glm::mat4& modelViewMatrix, const int32 drawOrder, const uint32 flags);

	void SetWidth(const uint32 width) { _width = width; }
	void SetHeight(const uint32 height) { _height = height; }

	uint32 GetWidth() const { return _width; }
	uint32 GetHeight() const { return _height; }

private:
	uint32 _width;
	uint32 _height;

	Material _material;
	QuadCommandBuffer _drawCmd;
};

NS_VG_END

#endif // __VGSPRITE_H__
