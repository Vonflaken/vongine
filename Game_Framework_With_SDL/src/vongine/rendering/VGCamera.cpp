#include "VGCamera.h"
#include "glm/gtc/matrix_transform.hpp"

NS_VG_BEGIN

std::shared_ptr<Camera> Camera::CreateOrtho(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	glm::mat4 projMat = glm::ortho(left, right, bottom, top, near, far);
	camera->SetProjectionMatrix(projMat);
	return camera;
}

std::shared_ptr<Camera> Camera::CreatePerspective(const float fov, const float aspectRatio, const float near, const float far)
{
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	glm::mat4 projMat = glm::perspective(fov, aspectRatio, near, far);
	camera->SetProjectionMatrix(projMat);
	return camera;
}

uint32 Camera::ProcessParentFlags(const glm::mat4& parentTransform, const uint32 parentFlags)
{
	uint32 processedFlags = Entity::ProcessParentFlags(parentTransform, parentFlags);

	if (processedFlags & FLAGS_TRANSFORM_DIRTY)
	{
		// Update View matrix
		glm::vec3 target = _position + GetTransformForwardOrientation();
		UpdateViewMatrix(target);
	}

	return processedFlags;
}

void Camera::UpdateViewMatrix(const glm::vec3& target)
{
	_viewMatrix = glm::lookAt(GetEye(), target, glm::vec3(0.f, 1.f, 0.f));
}

NS_VG_END
