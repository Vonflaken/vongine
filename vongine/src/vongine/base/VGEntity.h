#ifndef __VGENTITY_H__
#define __VGENTITY_H__

#include "VGMacros.h"
#include "VGTypes.h"

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

#include <memory>
#include <vector>

NS_VG_BEGIN

class DLLAPI Entity : std::enable_shared_from_this<Entity>
{
public:
	static std::shared_ptr<Entity> Create();
	static std::shared_ptr<Entity> Create(const glm::vec3& position);

	Entity();

	bool Init(const glm::vec3& position);

	/**
	* Enable/Disable to the engine for calling Entity::UpdateLogic() every frame
	*/
	void EnableUpdateLogic(const bool enabled);
	/**
	* Called every frame if is enabled. Intended to update Entity logic.
	*/
	virtual void UpdateLogic(const float deltaTime) {}

	void AddChild(const std::shared_ptr<Entity> entity);
	void DetachChild(const std::shared_ptr<Entity> entity);
	virtual void SetParent(const std::shared_ptr<Entity> parent);
	const std::shared_ptr<Entity> GetParent() const { return _parent.lock(); }

	virtual void SetPosition(const glm::vec3& position);
	const glm::vec3& GetPosition() const { return _position; }
	const glm::vec3 GetWorldPosition();

	virtual void SetEulerAngles(const glm::vec3& eulerAngles);
	glm::vec3 GetEulerAngles() const { return glm::eulerAngles(_rotation); }
	virtual void SetRotation(const glm::quat& rotation);
	const glm::quat& GetRotation() const { return _rotation; }

	virtual void SetScale(const glm::vec3& scale);
	const glm::vec3& GetScale() const { return _scale; }

	/**
	* @return Direction which is pointing the transform forward (z-axis), up (y-axis) and right (x-axis)
	*/
	glm::vec3 TransformForward() const;
	glm::vec3 TransformUp() const;
	glm::vec3 TransformRight() const;

	virtual void Prepare(const glm::mat4& parentTransform, const int32 localOrder, const uint32 parentFlags); /// Update entity state (transform, etc.) If needed and get ready for be drawn
	virtual void Draw(const glm::mat4& modelViewMatrix, const int32 drawOrder, const uint32 flags) {}

	/// Returns transform relative to parent
	const glm::mat4& GetToParentTransform();
	/// Returns transform relative to certain parent
	const glm::mat4 GetToParentTransform(const std::shared_ptr<Entity> ancestor);
	/// Returns Transform matrix (aka Model)
	const glm::mat4 GetWorldTransform(const glm::mat4& parentTransform);
	const glm::mat4& GetModelMatrix() const { return _modelMatrix; }
	
	void SetCameraTag(const uint32 tag) { _cameraTag = tag; }
	const uint32 GetCameraTag() const { return _cameraTag; }

protected:
	virtual uint32 ProcessParentFlags(const glm::mat4& parentTransform, const uint32 parentFlags); /// Update parent dependent state If needed

	/// Check whether or not entity's camera tag matchs with the tag of current rendering camera
	bool IsDrawableByRenderingCamera() const;

protected:
	enum {
		FLAG_TRANSFORM_DIRTY = (1 << 0)
	};

	glm::vec3 _position;
	glm::quat _rotation; // Rotation
	glm::vec3 _scale;

	glm::mat4 _transformMatrix; // Entity to parent transform
	glm::mat4 _modelMatrix; // Model matrix
	glm::mat4 _modelViewMatrix;

	bool _transformDirty;
	bool _transformUpdated; // Tell whether transform was updated or not in current frame

	std::weak_ptr<Entity> _parent;
	std::vector<std::shared_ptr<Entity>> _children;

	uint32 _cameraTag; // Entity drawable by camera with same tag

	int32 _onUpdateLogicId; // Identifier of this entity in global Update Logic event.
};

NS_VG_END

#endif // __VGENTITY_H__
