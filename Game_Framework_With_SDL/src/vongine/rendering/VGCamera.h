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

	Camera();

	void InitPerspective(const float fov, const float aspectRatio, const float near, const float far);
	void InitOrtho(const float left, const float right, const float bottom, const float top, const float near, const float far);

	virtual void SetParent(const std::shared_ptr<Entity> entity);

	virtual void SetPosition(const glm::vec3& position);
	virtual void SetEulerAngles(const glm::vec3& eulerAngles);
	virtual void SetScale(const glm::vec3& scale);

	const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
	const glm::mat4& GetViewMatrix();
	const glm::mat4& GetViewProjectionMatrix();

	const glm::vec3 GetEye() { return GetWorldPosition(); }

private:
	static std::shared_ptr<Camera> s_renderingCamera;

	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewProjectionMatrix;

	bool _viewMatrixDirty;
	bool _viewProjectionMatrixDirty;
};

NS_VG_END

#endif // __VGCAMERA_H__

