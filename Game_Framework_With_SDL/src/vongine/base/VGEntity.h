#ifndef __VGENTITY_H__
#define __VGENTITY_H__

#include "VGMacros.h"
#include "glm/glm.hpp"
#include "VGTypes.h"
#include <memory>
#include <vector>

NS_VG_BEGIN

class __declspec(dllexport) Entity : std::enable_shared_from_this<Entity>
{
public:
	static std::shared_ptr<Entity> Create();
	static std::shared_ptr<Entity> Create(const glm::vec3& position);

	Entity();
	virtual ~Entity() {}

	void AddChild(const std::shared_ptr<Entity> entity);
	void DetachChild(const std::shared_ptr<Entity> entity);
	virtual void SetParent(const std::shared_ptr<Entity> parent);
	const std::shared_ptr<Entity> GetParent() const { return _parent.lock(); }

	virtual void SetPosition(const glm::vec3& position);
	const glm::vec3& GetPosition() const { return _position; }
	const glm::vec3 GetWorldPosition();

	virtual void SetEulerAngles(const glm::vec3& eulerAngles);
	const glm::vec3& GetEulerAngles() const { return _eulerAngles; }

	virtual void SetScale(const glm::vec3& scale);
	const glm::vec3& GetScale() const { return _scale; }

	// Returns orientation in euler angles
	const glm::vec3 GetTransformForwardOrientation() const;

	virtual void Prepare(const glm::mat4& parentTransform, const uint32 parentFlags); // Update entity state (transform, etc.) If needed and get ready for be drawn
	virtual void Draw(const glm::mat4& modelViewTransform, const uint32 drawOrder, const uint32 flags) {}

	// Returns transform relative to parent
	const glm::mat4& GetToParentTransform();
	// Returns transform relative to certain parent
	const glm::mat4 GetToParentTransform(const std::shared_ptr<Entity> ancestor);
	// Returns Transform matrix (aka Model)
	const glm::mat4 GetWorldTransform(const glm::mat4& parentTransform);
	const glm::mat4& GetModelMatrix() const { return _modelMatrix; }
	
	void SetCameraTag(const uint32 tag) { _cameraTag = tag; }
	const uint32 GetCameraTag() const { return _cameraTag; }

protected:
	virtual uint32 ProcessParentFlags(const glm::mat4& parentTransform, const uint32 parentFlags); // Update parent dependent state If needed

	// Check whether or not entity's camera tag matchs with the tag of current rendering camera
	bool IsDrawableByRenderingCamera() const;

protected:
	enum {
		FLAGS_TRANSFORM_DIRTY = (1 << 0)
	};

	glm::vec3 _position;
	glm::vec3 _eulerAngles; // Rotation in euler angles
	glm::vec3 _scale;
	glm::mat4 _transformMatrix; // Entity to parent transform
	glm::mat4 _modelMatrix; // Model matrix
	glm::mat4 _modelViewMatrix;

	bool _transformDirty;
	bool _transformUpdated; // Tell whether transform was updated or not in current frame

	std::weak_ptr<Entity> _parent;
	std::vector<std::shared_ptr<Entity>> _children;

	uint32 _cameraTag; // Entity drawable by camera with same tag
};

NS_VG_END

#endif // __VGENTITY_H__
