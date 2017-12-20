#ifndef __VGSPRITE_H__
#define __VGSPRITE_H__

#include "VGMacros.h"
#include "base/VGEntity.h"
#include "rendering/VGMaterialProtocol.h"
#include "rendering/VGQuadCommandBuffer.h"
#include "physics/VGSimple2DCollision.h"
#include "2d/VGSpriteAnimation.h"

#include <unordered_map>

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
	/**
	* @param filename Name of spritesheet image file.
	* @param animsNames Pointer to array of std:string's.
	* @param anims Pointer to array of SpriteAnimation's.
	* @param defaultAnim Animation that will play by default at Sprite initialization (Opt).
	*/
	static std::shared_ptr<Sprite> CreateWithAnimations(const std::string& filename, std::string* animsNames, uint32* animsStartFrames, uint32* animsFramesCounts, const uint32 animsFrameW, const uint32 animsFrameH, const uint32 animsLength, const std::string& defaultAnim = "");

	Sprite();

	virtual bool Init(const std::string& filename, const glm::vec3& position, const uint32 width = 0, const uint32 height = 0);

	/**
	* Is neccessary call Sprite implementation of UpdateLogic function from children classes if is overrided.
	*/
	void UpdateLogic(const float deltaTime) override;

	virtual void Draw(const glm::mat4& modelViewMatrix, const int32 drawOrder, const uint32 flags);

	void SetSize(const Size& size) { _width = size.width; _height = size.height; }
	Size GetSize() const { return Size(_width, _height); }
	void SetWidth(const uint32 width) { _width = width; }
	void SetHeight(const uint32 height) { _height = height; }
	uint32 GetWidth() const { return _width; }
	uint32 GetHeight() const { return _height; }

	/**
	* Rotate 180 degrees in y-axis.
	*/
	void FlipY() { _rotation = _rotation * glm::quat(glm::vec3(0.f, glm::radians(180.f), 0.f)); }

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
	void SetCollisionBox(const uint32 width, const uint32 height) { _colBox.width = width; _colBox.height = height; }
	/**
	* Set position and other shape data in collision object.
	*/
	void UpdateCollisionShape();
	/**
	* Triggers when two Sprites collide each other.
	*/
	virtual void OnCollision(Sprite* other) {}

	//////////////// Sprite animation
	void SetUVFrame(const UVRect& uvRect);
	const UVRect& GetUVFrame() const { return _uvFrame; }

	void AddAnimation(const std::string& name, const uint32 frameW, const uint32 frameH, const uint32 startFrame, const uint32 framesCount);
	void PlayAnimation(const std::string& name, const bool loop, const bool playBackwards = false, const std::function<void(SpriteAnimation*)> finishedCallback = nullptr, const uint32 fps = 24);

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

	//////////// Sprite animation
	UVRect _uvFrame; // UV's defining the frame that must be drawn.
	std::unordered_map<std::string, SpriteAnimation> _animations;
	bool _uvFrameUpdated;
	std::string _currentAnimPlayingName;
};

NS_VG_END

#endif // __VGSPRITE_H__
