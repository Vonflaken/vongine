#include "VGEntity.h"
#include "rendering/VGCamera.h"
#include "base/VGUtils.h"

#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"

NS_VG_BEGIN

std::shared_ptr<Entity> Entity::Create()
{
	return Entity::Create(glm::vec3(0.f, 0.f, 0.f));
}

std::shared_ptr<Entity> Entity::Create(const glm::vec3& position)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	if (entity && entity->Init(position))
	{
		return entity;
	}

	return nullptr;
}

Entity::Entity()
: _position(0.f, 0.f, 0.f)
, _rotation(glm::vec3(0.f, 0.f, 0.f))
, _scale(1.f, 1.f, 1.f)
, _transformMatrix(1.f)
, _modelMatrix(1.f)
, _modelViewMatrix(1.f)
, _transformUpdated(true)
, _transformDirty(true)
, _cameraTag(1)
{}

bool Entity::Init(const glm::vec3& position)
{
	SetPosition(position);

	return true;
}

void Entity::Prepare(const glm::mat4& parentTransform, const int32 localOrder, const uint32 parentFlags)
{
	uint32 flags = ProcessParentFlags(parentTransform, parentFlags);

	// Self draw
	if (IsDrawableByRenderingCamera())
	{
		Draw(_modelViewMatrix, localOrder, flags);
	}

	int32 childOrder = 0;
	// Prepare children
	for (auto it = _children.begin(); it != _children.end(); it++)
	{
		(*it)->Prepare(_modelMatrix, childOrder, flags);
		childOrder++;
	}
}

uint32 Entity::ProcessParentFlags(const glm::mat4& parentTransform, const uint32 parentFlags)
{
	uint32 flags = parentFlags;

	// Set ON transform dirty bit If position, rotation, scale...have changed this frame
	flags |= (_transformUpdated ? FLAG_TRANSFORM_DIRTY : 0);

	bool transformDirty = flags & FLAG_TRANSFORM_DIRTY;
	if (transformDirty)
	{
		// Update Model
		_modelMatrix = GetWorldTransform(parentTransform);
	}

	auto cam = Camera::s_renderingCamera;
	// Compute MV matrix just with cameras which render this entity
	if (IsDrawableByRenderingCamera() && cam && (cam->IsViewMatrixUpdated() || transformDirty))
	{
		_modelViewMatrix = cam->GetViewMatrix() * _modelMatrix;
	}

	_transformUpdated = false;

	return flags;
}

const glm::mat4& Entity::GetToParentTransform()
{
	if (_transformDirty)
	{
		glm::mat4 scaling = glm::scale(_scale); // scale

		// TODO: Offset position for rotating on a different point than origin
		glm::mat4 rotationMat = glm::toMat4(_rotation); // rotation

		glm::mat4 translation = glm::translate(_position); // translate

		// T * R * S
		_transformMatrix = translation * rotationMat * scaling;
	}

	_transformDirty = false;

	return _transformMatrix;
}

const glm::mat4 Entity::GetToParentTransform(const std::shared_ptr<Entity> ancestor)
{
	glm::mat4 transform(GetToParentTransform());

	for (auto parent = _parent.lock(); parent && parent != ancestor; parent = parent->GetParent())
	{
		transform = parent->GetToParentTransform() * transform;
	}

	return transform;
}

const glm::mat4 Entity::GetWorldTransform(const glm::mat4& parentTransform)
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
	if (position == _position) // No update If equals
		return;

	_position = position; 

	_transformUpdated = _transformDirty = true;
}

void Entity::SetEulerAngles(const glm::vec3& eulerAngles)
{ 
	glm::quat newRot(
		glm::vec3(
			glm::radians(eulerAngles.x), // pitch
			glm::radians(eulerAngles.y), // yaw
			glm::radians(eulerAngles.z))); // roll

	if (newRot != _rotation) // No update If equals
	{
		_rotation = newRot;

		_transformUpdated = _transformDirty = true;
	}
}

void Entity::SetRotation(const glm::quat& rotation)
{
	if (rotation != _rotation) // No update If equals
	{
		_rotation = rotation;

		_transformUpdated = _transformDirty = true;
	}
}

void Entity::SetScale(const glm::vec3& scale)
{
	if (scale == _scale) // No update If equals
		return;

	_scale = scale; 

	_transformUpdated = _transformDirty = true;
}

void Entity::AddChild(const std::shared_ptr<Entity> entity)
{
	VGASSERT(entity, "Trying to add a null child to an entity!")
	// Add to children array
	_children.push_back(entity);
	// Set 'entity' parent
	entity->SetParent(shared_from_this());
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

void Entity::SetParent(const std::shared_ptr<Entity> parent)
{
	_parent = parent;

	_transformUpdated = _transformDirty = true;
}

glm::vec3 Entity::GetForwardDir() const
{
	return _rotation * glm::vec3(0.f, 0.f, 1.f);
}

bool Entity::IsDrawableByRenderingCamera() const
{
	return Camera::s_renderingCamera ? (Camera::s_renderingCamera->GetDrawablesMask() & GetCameraTag()) != 0 : false;
}

NS_VG_END
