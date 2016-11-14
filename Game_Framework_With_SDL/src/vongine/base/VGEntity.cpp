#include "VGEntity.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

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
, _transformMatrix() // identity
, _modelMatrix()
, _transformUpdated(true)
, _transformDirty(true)
{
}

void Entity::Prepare(const glm::mat4& parentTransform, const uint32 parentFlags)
{
	uint32 flags = ProcessParentFlags(parentTransform, parentFlags);

	// Prepare children
	for (auto it = _children.begin(); it != _children.end(); it++)
	{		
		(*it)->Prepare(_modelMatrix, flags);
	}
}

uint32 Entity::ProcessParentFlags(const glm::mat4& parentTransform, const uint32 parentFlags)
{
	uint32 flags = parentFlags;

	// Set ON transform dirty bit If position, rotation, scale...have changed this frame
	flags |= (_transformUpdated ? FLAGS_TRANSFORM_DIRTY : 0);

	if (flags & FLAGS_TRANSFORM_DIRTY)
	{
		// Update Model
		_modelMatrix = CalculateModel(parentTransform);
	}

	_transformUpdated = false;

	return flags;
}

const glm::mat4& Entity::GetToParentTransform()
{
	if (_transformDirty)
	{
		glm::mat4 mat;

		glm::translate(mat, _position); // translate

		// rotate
		glm::rotate(mat, _eulerAngles.x, glm::vec3(1.f, 0.f, 0.f));
		glm::rotate(mat, _eulerAngles.y, glm::vec3(0.f, 1.f, 0.f));
		glm::rotate(mat, _eulerAngles.z, glm::vec3(0.f, 0.f, 1.f));

		glm::scale(mat, _scale); // scale

		_transformMatrix = mat;
	}

	_transformDirty = false;

	return _transformMatrix;
}

const glm::mat4 Entity::GetToParentTransform(const std::shared_ptr<Entity> ancestor)
{
	glm::mat4 transform(GetToParentTransform());

	for (auto parent = _parent.lock(); parent && parent != ancestor; parent = parent->GetParent().lock())
	{
		transform = parent->GetToParentTransform() * transform;
	}

	return transform;
}

const glm::mat4 Entity::CalculateModel(const glm::mat4& parentTransform)
{
	return parentTransform * GetToParentTransform();
}

const glm::vec3 Entity::GetWorldPosition()
{
	glm::vec3 worldPos;
	if (!_transformUpdated)
	{
		worldPos = _modelMatrix * glm::vec4(glm::vec3(0.f), 1.f);
	}
	else
	{
		worldPos = GetToParentTransform(nullptr) * glm::vec4(glm::vec3(0.f), 1.f);
	}

	return worldPos;
}

void Entity::SetPosition(const glm::vec3& position)
{
	_position = position; 

	_transformUpdated = _transformDirty = true;
}

void Entity::SetEulerAngles(const glm::vec3& eulerAngles)
{ 
	_eulerAngles = eulerAngles; 

	_transformUpdated = _transformDirty = true;
}

void Entity::SetScale(const glm::vec3& scale)
{
	_scale = scale; 

	_transformUpdated = _transformDirty = true;
}

void Entity::AddChild(const std::shared_ptr<Entity> entity)
{
	// Add to children array
	_children.push_back(entity);
	// Set 'entity' parent
	entity->SetParent(std::shared_ptr<Entity>(this));
}

void Entity::DetachChild(const std::shared_ptr<Entity> entity)
{
	for (auto it = _children.begin(); it != _children.end(); it++)
	{
		if (*it == entity)
		{
			// Notify entity that has not parent now
			(*it)->SetParent(nullptr);
			// Remove entity from array
			_children.erase(it);
			break;
		}
	}
}

void Entity::SetParent(const std::shared_ptr<Entity> entity)
{
	_parent = entity;

	_transformUpdated = _transformDirty = true;

}

const glm::vec3 Entity::GetTransformForwardOrientation() const
{
	return glm::quat(_eulerAngles) * glm::vec3(0.f, 0.f, 1.f);
}

NS_VG_END
