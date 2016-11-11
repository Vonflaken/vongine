#ifndef __VGCAMERA_H__
#define __VGCAMERA_h__

#include "VGMacros.h"
#include "base/VGEntity.h"

NS_VG_BEGIN

class __declspec(dllexport) Camera : public Entity
{
public:
	static std::shared_ptr<Camera> CreateOrtho(const float left, const float right, const float bottom, const float top, const float near, const float far);
	static std::shared_ptr<Camera> CreatePerspective(const float fov, const float aspectRatio, const float near, const float far);

	void SetProjectionMatrix(const glm::mat4& projMat) { _projectionMatrix = projMat; }

	const glm::vec3 GetEye() { return GetWorldPosition(); }

private:


private:
	static std::shared_ptr<Camera> s_renderingCamera;

	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
};

NS_VG_END

#endif // __VGCAMERA_H__

