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

	virtual void AddChild(const std::shared_ptr<Entity> entity);
	/**
	* @return bool Whereas or not entity was removed successfuly.
	*/
	bool DetachChild(const std::shared_ptr<Entity> entity);
	/**
	* Search deep in hierarchy.
	* @return bool Whereas or not entity was removed successfuly.
	*/
	bool DetachChildRecursive(const std::shared_ptr<Entity> entity);
	virtual void SetParent(const std::shared_ptr<Entity> parent);
	const std::shared_ptr<Entity> GetParent() const { return _parent.lock(); }

	virtual void SetPosition(const glm::vec3& position);
	/**
	* Sets 2D position, keeps same 'z'.
	*/
	void SetPosition(const float x, const float y);
	const glm::vec3& GetPosition() const { return _position; }
	glm::vec3 GetWorldPosition();
	Point GetAbsolute2DPosition();

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
	/**
	* Sets tag to all entities in hierarchy.
	*/
	void SetCameraTagRecursive(const uint32 tag);
	const uint32 GetCameraTag() const { return _cameraTag; }

	void SetVisible(const bool val) { _isVisible = val; }
	bool IsVisible() const { return _isVisible; }

	bool IsStarted() const { return _started; }

	/*******************************************************************************************
	* OnStart, OnAttach and OnDetach functions never should being called explicitly by user.
	* Call to implementation of base class is mandatory if you ever override them.
	*/
	/**
	* Called first time that Entity is added to scene graph.
	*/
	virtual void OnStart();
	/**
	* Called every time that Entity is added to scene graph.
	*/
	virtual void OnAttach() {}
	/**
	* Called when is detached from parent. It leaves the scene graph.
	*/
	virtual void OnDetach() {}

protected:
	/**
	* Update parent dependent state if needed.
	*/
	virtual uint32 ProcessParentFlags(const glm::mat4& parentTransform, const uint32 parentFlags);

	/**
	* Check whether or not camera tag of entity matches with the tag of current rendering camera.
	*/
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

	bool _isVisible; // Whereas or not the entity will be rendered
	bool _started; // Whereas or not the Entity was added for the first time to scene graph, thus, OnStart already called.
};

NS_VG_END

#endif // __VGENTITY_H__
