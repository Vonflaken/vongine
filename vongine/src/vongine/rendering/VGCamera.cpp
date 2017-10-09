#include "VGCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "ogl/glew.h"

NS_VG_BEGIN

std::shared_ptr<Camera> Camera::s_renderingCamera = nullptr;


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
, _drawablesMask(DEFAULT_CAMERA_TAG)
, _clearBuffersMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
, _viewMatrixUpdated(false)
, _cameraOrder(0)
{}

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

		glm::mat4 translate = glm::translate(-_position);
		// Since we know the rotation matrix is orthonormalized, we can simply 
		// transpose the rotation matrix instead of inversing.
		glm::mat4 rotate = glm::transpose(glm::toMat4(_rotation));

		_viewMatrix = translate * rotate;

		_viewMatrixDirty = false;
	}

	return _viewMatrix;
}

void Camera::SetPosition(const glm::vec3& position)
{
	Entity::SetPosition(position);

	_viewProjectionMatrixDirty = _viewMatrixDirty = _viewMatrixUpdated = true;
}

void Camera::SetEulerAngles(const glm::vec3& eulerAngles)
{
	Entity::SetEulerAngles(eulerAngles);

	_viewProjectionMatrixDirty = _viewMatrixDirty = _viewMatrixUpdated = true;
}

void Camera::Use()
{
	// Clear buffers
	glClear(_clearBuffersMask);
}

void Camera::Dispose()
{
	_viewMatrixUpdated = false;
}

void Camera::SetClearBuffers(const bool color, const bool depth, const bool stencil)
{
	uint32 newMask = 0;
	if (color)
		newMask |= GL_COLOR_BUFFER_BIT;
	if (depth)
		newMask |= GL_DEPTH_BUFFER_BIT;
	if (stencil)
		newMask |= GL_STENCIL_BUFFER_BIT;

	_clearBuffersMask = newMask;
}

NS_VG_END
