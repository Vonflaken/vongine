#ifndef __VGCAMERA_H__
#define __VGCAMERA_H__

#include "VGMacros.h"
#include "base/VGEntity.h"

NS_VG_BEGIN

class DLLAPI Camera : public Entity
{
public:
	enum
	{
		DEFAULT_CAMERA_TAG = (1 << 0), 
		CAMERA_TAG_1 = (1 << 1), 
		CAMERA_TAG_2 = (1 << 2), 
		CAMERA_TAG_3 = (1 << 3), 
		CAMERA_TAG_4 = (1 << 4), 
		DEFAULT_CAMERA_UI = (1 << 5), 
		CAMERA_UI_1 = (1 << 6)
	};

	static std::shared_ptr<Camera> CreateOrtho(const float left, const float right, const float bottom, const float top, const float near, const float far);
	static std::shared_ptr<Camera> CreatePerspective(const float fov, const float aspectRatio, const float near, const float far);

	Camera();

	void InitPerspective(const float fov, const float aspectRatio, const float near, const float far);
	void InitOrtho(const float left, const float right, const float bottom, const float top, const float near, const float far);

	/**
	* Call before render loop
	*/
	void Use();
	/**
	* Call after render loop
	*/
	void Dispose();

	// FIXME: Not sure about update the View matrix If camera has a new parent. Relative rotation is the concern.
	virtual void SetPosition(const glm::vec3& position) override;
	virtual void SetEulerAngles(const glm::vec3& eulerAngles) override;
	virtual void SetScale(const glm::vec3& scale) override {} // Scale in cameras It has no sense

	bool IsViewMatrixUpdated() const { return _viewMatrixUpdated; }

	void SetDrawablesMask(const uint32 mask) { _drawablesMask = mask; }
	const uint32 GetDrawablesMask() const { return _drawablesMask; }

	const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
	const glm::mat4& GetViewMatrix();
	const glm::mat4& GetViewProjectionMatrix();

	const glm::vec3 GetEye() { return GetWorldPosition(); }

	void SetCameraOrder(const uint32 order) { _cameraOrder = order; }
	uint32 GetCameraOrder() const { return _cameraOrder; }

	void SetClearBuffers(const bool color, const bool depth, const bool stencil);

public:
	static std::shared_ptr<Camera> s_renderingCamera;

private:
	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewProjectionMatrix;

	bool _viewMatrixDirty;
	bool _viewProjectionMatrixDirty;
	bool _viewMatrixUpdated; /// Whether or not View matrix was updated in current frame

	uint32 _drawablesMask; /// Contains camera tags that will be able to draw by this camera. Default is draw DEFAULT cam
	uint32 _clearBuffersMask; /// 'On bits' are the buffers gonna be cleared. Default value is clear COLOR and DEPTH buffers

	uint32 _cameraOrder; /// Asc order which cameras are rendered
};

NS_VG_END

#endif // __VGCAMERA_H__

