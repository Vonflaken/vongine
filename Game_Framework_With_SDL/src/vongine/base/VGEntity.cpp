#include "VGEntity.h"
#include "glm/gtc/matrix_transform.hpp"

NS_VG_BEGIN

std::shared_ptr<Entity> Entity::Create()
{
	return Entity::Create(glm::vec3(0.f, 0.f, 0.f));
}

std::shared_ptr<Entity> Entity::Create(const glm::vec3& position)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	return entity;
}

Entity::Entity()
: _position(0.f, 0.f, 0.f)
, _eulerAngles(0.f, 0.f, 0.f)
, _scale(1.f, 1.f, 1.f)
, _transform() // identity
, _stateFlags(0)
, _parent(nullptr)
{
}

void Entity::Prepare(const glm::mat4& parentTransform, const uint32 parentFlags)
{
	uint32 mergedFlags = parentFlags | _stateFlags;

	if (mergedFlags & FLAGS_TRANSFORM_DIRTY)
	{
		// Update transform

		_transform = parentTransform * GetToParentTranform();
		_stateFlags |= FLAGS_TRANSFORM_DIRTY; // Set dirty for propagate transform update to childs
	}

	// Prepare children
	for (auto it = _children.begin(); it != _children.end(); it++)
	{		
		(*it)->Prepare(_transform, _stateFlags);
	}

	_stateFlags |= ~FLAGS_TRANSFORM_DIRTY; // Set transform bit as updated
}

const glm::mat4& Entity::GetToParentTranform() const
{
	glm::mat4 mat;
	
	glm::translate(mat, _position); // translate
	
	// rotate
	glm::rotate(mat, _eulerAngles.x, glm::vec3(1.f, 0.f, 0.f));
	glm::rotate(mat, _eulerAngles.y, glm::vec3(0.f, 1.f, 0.f));
	glm::rotate(mat, _eulerAngles.z, glm::vec3(0.f, 0.f, 1.f));

	glm::scale(mat, _scale); // scale

	return mat;
}

void Entity::SetPosition(const glm::vec3& position)
{
	_stateFlags |= FLAGS_TRANSFORM_DIRTY;

	_position = position; 
}

void Entity::SetEulerAngles(const glm::vec3& eulerAngles)
{ 
	_stateFlags |= FLAGS_TRANSFORM_DIRTY;

	_eulerAngles = eulerAngles; 
}

void Entity::SetScale(const glm::vec3& scale)
{ 
	_stateFlags |= FLAGS_TRANSFORM_DIRTY;

	_scale = scale; 
}

void Entity::AddChild(const std::shared_ptr<Entity> entity)
{
	// Add to children array
	_children.push_back(entity);
	// Set 'entity' parent
	entity->SetParent(std::shared_ptr<Entity>(this));
	// Will update transform, now transform must be relative to parent
	AddFlags(FLAGS_TRANSFORM_DIRTY);
}

void Entity::AddFlags(const uint32 flags)
{
	_stateFlags |= flags;
}

NS_VG_END
