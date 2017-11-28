#ifndef __VGSPRITE_H__
#define __VGSPRITE_H__

#include "VGMacros.h"
#include "base/VGEntity.h"
#include "rendering/VGMaterialProtocol.h"
#include "rendering/VGQuadCommandBuffer.h"
#include "physics/VGSimple2DCollision.h"

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

	void SetCollision(const Simple2DCollisionType colType);
	Simple2DCollision const * GetCollision() const { return _simpleCollision.get(); };
	bool CheckCollision(Sprite* other);
	/**
	* Provide custom radius for circle collision.
	*/
	void SetCollisionRadius(const float radius) { _colRadius = radius; }
	/**
	* Provide custom Size for rect collision.
	*/
	void SetCollisionBox(const float width, const float height) { _colBox.width = width; _colBox.height = height; }
	/**
	* Set position and other shape data in collision object.
	*/
	void UpdateCollisionShape();
	/**
	* Triggers when two Sprites collide each other.
	*/
	virtual void OnCollision(Sprite* other) {}

private:
	/**
	* Get collision box.
	* @return Size User defined values if did, Sprite size otherwise.
	*/
	Size GetColBox() const;
	/**
	* Get collision radius.
	* @return float User defined value if did, Sprite largest axis otherwise.
	*/
	float GetColRadius() const;

public:
	static std::vector<std::weak_ptr<Sprite>> s_spritesWithCollision; // Collection of Sprites with a Simple2DCollision defined.

private:
	uint32 _width;
	uint32 _height;

	Material _material;
	QuadCommandBuffer _drawCmd;

	std::unique_ptr<Simple2DCollision> _simpleCollision;
	float _colRadius;
	Size _colBox;
};

NS_VG_END

#endif // __VGSPRITE_H__
