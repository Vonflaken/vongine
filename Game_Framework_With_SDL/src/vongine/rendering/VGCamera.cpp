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

NS_VG_END
