#include "VGCamera.h"
#include "glm/gtc/matrix_transform.hpp"

NS_VG_BEGIN

std::shared_ptr<Camera> Camera::CreateOrtho(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	camera->InitOrtho(left, right, bottom, top, near, far);
	return camera;
}

std::shared_ptr<Camera> Camera::CreatePerspective(const float fov, const float aspectRatio, const float near, const float far)
{
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	camera->InitPerspective(fov, aspectRatio, near, far);
	return camera;
}

Camera::Camera()
: _viewMatrixDirty(true)
{
}

void Camera::InitPerspective(const float fov, const float aspectRatio, const float near, const float far)
{
	_projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
	_viewProjectionMatrixDirty = true;
}

void Camera::InitOrtho(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	_projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
	_viewProjectionMatrixDirty = true;
}

const glm::mat4& Camera::GetViewProjectionMatrix()
{
	glm::mat4 view = GetViewMatrix();
	if (_viewProjectionMatrixDirty)
	{
		_viewProjectionMatrix = _projectionMatrix * view;

		_viewProjectionMatrixDirty = false;
	}

	return _viewProjectionMatrix;
}

const glm::mat4& Camera::GetViewMatrix()
{
	if (_viewMatrixDirty)
	{
		// Update View matrix
		glm::vec3 target = _position + GetTransformForwardOrientation();
		_viewMatrix = glm::lookAt(GetEye(), target, glm::vec3(0.f, 1.f, 0.f)); // Set

		_viewMatrixDirty = false;
	}

	return _viewMatrix;
}

void Camera::SetParent(const std::shared_ptr<Entity> entity)
{
	Entity::SetParent(entity);

	_viewProjectionMatrixDirty = _viewMatrixDirty = true;
}

void Camera::SetPosition(const glm::vec3& position)
{
	Entity::SetPosition(position);

	_viewProjectionMatrixDirty = _viewMatrixDirty = true;
}

void Camera::SetEulerAngles(const glm::vec3& eulerAngles)
{
	Entity::SetEulerAngles(eulerAngles);

	_viewProjectionMatrixDirty = _viewMatrixDirty = true;
}

void Camera::SetScale(const glm::vec3& scale)
{
	Entity::SetScale(scale);

	_viewProjectionMatrixDirty = _viewMatrixDirty = true;
}

NS_VG_END
