#ifndef __VGENTITY_H__
#define __VGENTITY_H__

#include "VGMacros.h"
#include "glm/glm.hpp"
#include "VGTypes.h"
#include <memory>
#include <vector>

NS_VG_BEGIN

class __declspec(dllexport) Entity
{
	enum {
		FLAGS_TRANSFORM_DIRTY = (1 << 0)
	};

public:
	static std::shared_ptr<Entity> Create();
	static std::shared_ptr<Entity> Create(const glm::vec3& position);

	Entity();
	virtual ~Entity() {}

	void AddChild(const std::shared_ptr<Entity> entity);
	void DetachChild(const std::shared_ptr<Entity> entity);
	void SetParent(const std::shared_ptr<Entity> entity);

	// Merge 'flags' with entity flags
	void AddFlags(const uint32 flags);

	void SetPosition(const glm::vec3& position);
	const glm::vec3& GetPosition() const { return _position; }
	const glm::vec3 GetWorldPosition() const;

	void SetEulerAngles(const glm::vec3& eulerAngles);
	const glm::vec3& GetEulerAngles() const { return _eulerAngles; }

	void Entity::SetScale(const glm::vec3& scale);
	const glm::vec3& GetScale() const { return _scale; }

	virtual void Prepare(const glm::mat4& parentTransform, const uint32 parentFlags); // Update transform If needed
	virtual void Draw() {}

	// Returns transform relative to parent
	const glm::mat4 GetToParentTranform() const;
	

protected:
	glm::vec3 _position;
	glm::vec3 _eulerAngles; // Rotation in euler angles
	glm::vec3 _scale;
	glm::mat4 _transform;

	uint32 _stateFlags;

	std::weak_ptr<Entity> _parent;
	std::vector<std::shared_ptr<Entity>> _children;
};

NS_VG_END

#endif // __VGENTITY_H__
