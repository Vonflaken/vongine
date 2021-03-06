#include "VGEntity.h"
#include "rendering/VGCamera.h"
#include "base/VGUtils.h"
#include "base/VGCoreManager.h"
#include "base/VGScene.h"

#include "glm/gtx/transform.hpp"

NS_VG_BEGIN

using namespace utils;

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
, _modelViewIsDirty(true)
, _cameraTag(1)
, _onUpdateLogicId(-1)
, _stateFlags(FLAGS_DEFAULT_STATE)
, _accumulateFlags(0)
{}

Entity::~Entity()
{
	// Clean presence of this Entity in event callbacks
	EnableUpdateLogic(false);
}

bool Entity::Init(const glm::vec3& position)
{
	SetPosition(position);

	return true;
}

void Entity::EnableUpdateLogic(const bool enabled)
{
	if (enabled && _onUpdateLogicId < 0)
	{
		// Hook to global Update Logic event
		_onUpdateLogicId = CoreManager::GetInstance().EventMgr()->onUpdateLogic.On(this);
	}
	else if (!enabled && _onUpdateLogicId >= 0)
	{
		// Remove from global Update Logic event
		CoreManager::GetInstance().EventMgr()->onUpdateLogic.RemoveCallback(_onUpdateLogicId);
		_onUpdateLogicId = -1; // Set invalid value
	}
}

void Entity::Prepare(const glm::mat4& parentTransform, const int32 localOrder, const uint32 parentFlags)
{
	uint32 flags = ProcessParentFlags(parentTransform, parentFlags);

	// Self draw
	if (IsDrawableByRenderingCamera() && IsActive() && IsVisible())
	{
		if (_accumulateFlags)
		{
			Draw(_modelViewMatrix, localOrder, _accumulateFlags | flags);
			_accumulateFlags = 0;
		}
		else
		{
			Draw(_modelViewMatrix, localOrder, flags);
		}
	}
	else
	{
		_accumulateFlags |= flags; // Accumulate states, faster than check a condition
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
		_modelViewIsDirty = true;
	}

	auto cam = Camera::s_renderingCamera;
	// Compute MV matrix just for cameras which render this entity
	if (IsDrawableByRenderingCamera() && cam && (cam->IsViewMatrixUpdated() || transformDirty || _modelViewIsDirty))
	{
		_modelViewMatrix = cam->GetViewMatrix() * _modelMatrix;
		_modelViewIsDirty = false;
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

glm::vec3 Entity::GetWorldPosition()
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

void Entity::SetAbsolute2DPosition(const float x, const float y)
{
	SetWorldPosition(glm::vec3(x, y, GetWorldPosition().z));
}

Point Entity::GetAbsolute2DPosition()
{
	glm::vec3 absolute3DPos = GetWorldPosition();
	return { absolute3DPos.x, absolute3DPos.y };
}

void Entity::SetPosition(const glm::vec3& position)
{
	if (position == _position) // No update If equals
		return;

	_position = position; 

	_transformUpdated = _transformDirty = true;
}

void Entity::SetPosition(const float x, const float y) // 2D
{
	SetPosition(glm::vec3(x, y, _position.z));
}

void Entity::SetWorldPosition(const glm::vec3& worldPosition)
{
	auto toLocalMatrix = glm::inverse(GetToParentTransform(nullptr) * glm::inverse(GetToParentTransform()));
	glm::vec3 localPosition = toLocalMatrix * glm::vec4(worldPosition, 1.f);
	SetPosition(localPosition);
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
	VGASSERT(entity, "Trying to add a null child to an entity!");
	VGASSERT(!entity->GetParent(), "Trying to add a child that has already a parent!");

	// Add to children array
	_children.push_back(entity);
	// Set 'entity' parent
	entity->SetParent(shared_from_this());

	// Update local position of child
	glm::vec3 parentWorldPos = GetWorldPosition();
	glm::vec3 childWorldPos = entity->GetWorldPosition();
	entity->SetPosition(childWorldPos - parentWorldPos); // Offset between child world and parent world

	// Propagate the Scene that the parent belongs to
	entity->SetSceneRecursive(_scene.lock());

	// If parent Scene is the running one then call OnStart (if not started yet) in all 'entity' hyerarchy
	if (!_scene.expired())
	{
		if (_scene.lock().get() == CoreManager::GetInstance().GetRunningScene())
			entity->OnStartRecursive();
	}

	entity->OnAttach();
}

bool Entity::DetachChild(const std::shared_ptr<Entity> entity)
{
	for (auto it = _children.begin(); it != _children.end(); it++)
	{
		if (*it == entity)
		{
			(*it)->OnDetach();

			// Notify entity that has not parent now
			(*it)->SetParent(nullptr);
			// Remove entity from array
			_children.erase(it);

			/**
			* WARNING: If there are not external strong refs, weak refs and raw ptrs to this object will be invalid at this point.
			*/

			return true;
		}
	}
	return false;
}

bool Entity::DetachChildRecursive(const std::shared_ptr<Entity> entity)
{
	// Search in inmediate children
	bool found = DetachChild(entity);
	if (!found)
	{
		// Search in children of children
		for (auto it = _children.begin(); it != _children.end(); it++)
		{
			found = (*it)->DetachChildRecursive(entity);
			if (found)
				break;
		}
	}
	return found;
}

void Entity::SetParent(const std::shared_ptr<Entity> parent)
{
	_parent = parent;

	_transformUpdated = _transformDirty = true;
}

bool Entity::IsActive() const
{
	bool active = _stateFlags & FLAG_ACTIVE;
	if (active) // Still can be considered inactive if is not in running scene
	{
		if (!_scene.expired())
			active = (_scene.lock().get() == CoreManager::GetInstance().GetRunningScene());
	}
	return active;
}

void Entity::OnStart()
{
	_stateFlags |= FLAG_STARTED;
}

void Entity::OnStartRecursive()
{
	if (!IsStarted())
		OnStart();

	for (auto it = _children.begin(); it != _children.end(); it++)
	{
		(*it)->OnStartRecursive();
	}
}

glm::vec3 Entity::TransformForward() const
{
	return _rotation * glm::vec3(0.f, 0.f, 1.f);
}

glm::vec3 Entity::TransformUp() const
{
	return _rotation * glm::vec3(0.f, 1.f, 0.f);
}

glm::vec3 Entity::TransformRight() const
{
	return _rotation * glm::vec3(1.f, 0.f, 0.f);
}

bool Entity::IsDrawableByRenderingCamera() const
{
	return Camera::s_renderingCamera ? (Camera::s_renderingCamera->GetDrawablesMask() & GetCameraTag()) != 0 : false;
}

void Entity::SetCameraTagRecursive(const uint32 tag)
{
	for (uint32 i = 0; i < _children.size(); i++)
	{
		// Self set
		_children[i]->SetCameraTag(tag);
		// Set in children
		_children[i]->SetCameraTagRecursive(tag);
	}
}

void Entity::SetScene(const std::shared_ptr<Scene> scene)
{
	_scene = scene;
}

void Entity::SetSceneRecursive(const std::shared_ptr<Scene> scene)
{
	SetScene(scene);
	for (auto it = _children.begin(); it != _children.end(); it++)
	{
		(*it)->SetSceneRecursive(scene);
	}
}

NS_VG_END
