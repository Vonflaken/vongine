#ifndef __VGENTITY_H__
#define __VGENTITY_H__

#include "VGMacros.h"
#include "VGTypes.h"

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

#include <memory>
#include <vector>

NS_VG_BEGIN

class Scene;

class DLLAPI Entity : public std::enable_shared_from_this<Entity>
{
public:
	static std::shared_ptr<Entity> Create();
	static std::shared_ptr<Entity> Create(const glm::vec3& position);

	Entity();
	virtual ~Entity();

	virtual bool Init(const glm::vec3& position);

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

	/**
	* Set local position.
	*/
	virtual void SetPosition(const glm::vec3& position);
	/**
	* Sets local 2D position, keeps same 'z'.
	*/
	void SetPosition(const float x, const float y);
	/**
	* Get local position.
	*/
	const glm::vec3& GetPosition() const { return _position; }
	void SetWorldPosition(const glm::vec3& worldPosition);
	void SetAbsolute2DPosition(const float x, const float y);
	glm::vec3 GetWorldPosition();
	/**
	* Alias for a "GetWorld2DPosition" func.
	*/
	Point GetAbsolute2DPosition();
	/**
	* Moves the transform in the direction and distance of 'translation'.
	*/
	void Translate(const glm::vec3& translation) { SetPosition(GetPosition() + translation); }

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

	void SetName(const std::string& name) { _name = name; }
	const std::string& GetName() const { return _name; }

	void SetVisible(const bool val) { (val) ? _stateFlags |= FLAG_VISIBLE : _stateFlags &= ~FLAG_VISIBLE; }
	bool IsVisible() const { return (_stateFlags & FLAG_VISIBLE) != 0; }
	void SetActive(const bool active) { (active) ? _stateFlags |= FLAG_ACTIVE : _stateFlags &= ~FLAG_ACTIVE; }
	/**
	* Two scenarios where a entity is considered inactive: was previously deactivated or is not in the running scene graph.
	* Inactive entities won't be rendered or updated.
	*/
	bool IsActive() const;
	bool IsStarted() const { return (_stateFlags & FLAG_STARTED) != 0; }

	/*******************************************************************************************
	* OnStart, OnAttach and OnDetach functions never should being called explicitly by user.
	* Call to implementation of base class is mandatory if you ever override them.
	*/
	/**
	* Called first time that Entity is added to a running scene graph.
	*/
	virtual void OnStart();
	void OnStartRecursive();
	/**
	* Called every time that Entity is attached to a parent.
	*/
	virtual void OnAttach() {}
	/**
	* Called every time that Entity is detached from parent. It leaves its current graph.
	*/
	virtual void OnDetach() {}


	/**
	* Set scene that this Entity belongs to.
	*/
	void SetScene(const std::shared_ptr<Scene> scene);
	void SetSceneRecursive(const std::shared_ptr<Scene> scene);

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
		FLAG_TRANSFORM_DIRTY = (1 << 0), // Whereas or not the Entity transform values were changed.
		FLAG_VISIBLE = (1 << 1), // Whereas or not the Entity will render.
		FLAG_STARTED = (1 << 2), // Whereas or not the Entity was added for the first time to a running scene graph, thus, OnBecomeActive(...) already called.
		FLAG_ACTIVE = (1 << 3), // Whereas or not the Entity won't be rendered or updated.

		FLAGS_DEFAULT_STATE = FLAG_VISIBLE | FLAG_ACTIVE // State flags ON by default.
	};

	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

	glm::mat4 _transformMatrix; // Entity to parent transform.
	glm::mat4 _modelMatrix; // Model matrix.
	glm::mat4 _modelViewMatrix;

	bool _transformDirty;
	bool _transformUpdated; // Tell whether transform was updated or not in current frame.
	bool _modelViewIsDirty;
	uint32 _stateFlags; // Holds Entity states per bit. Bitwise AND op against enum FLAG values above in order to find out certain state value.

	std::weak_ptr<Entity> _parent;
	std::vector<std::shared_ptr<Entity>> _children;

	uint32 _cameraTag; // Entity drawable by camera with same tag.
	int32 _onUpdateLogicId; // Identifier of Update Logic signal slot for this Entity. Use for disconnecting from the event.
	std::string _name; // Name of Entity, for identification purposes.

	std::weak_ptr<Scene> _scene; // Scene that entity belongs to. Null if is not in a scene graph.
 
	/** 
	* Accumulate flags during Prepare time each time Entity doesn't drawn.
	* Used so that the Entity can tell that its transform was updated, etc. when its Draw func get called.
	*/
	uint32 _accumulateFlags;
};

NS_VG_END

#endif // __VGENTITY_H__
