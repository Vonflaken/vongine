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
	const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
	const glm::mat4 GetViewProjectionMatrix() const { return _projectionMatrix * _viewMatrix; }

	const glm::vec3 GetEye() { return GetWorldPosition(); }

	void UpdateViewMatrix(const glm::vec3& target);

protected:
	virtual uint32 ProcessParentFlags(const glm::mat4& parentTransform, const uint32 parentFlags);

private:
	static std::shared_ptr<Camera> s_renderingCamera;

	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
};

NS_VG_END

#endif // __VGCAMERA_H__

