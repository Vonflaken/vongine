#include "VGUICanvas.h"
#include "rendering/VGCamera.h"
#include "base/VGCoreManager.h"
#include "base/VGScene.h"

NS_VG_BEGIN

namespace ui
{
	std::shared_ptr<Canvas> Canvas::Create(const Size& size)
	{
		auto canvas = std::make_shared<Canvas>();
		if (canvas->Init(glm::vec3(0.f, 0.f, 0.f), size))
		{
			return canvas;
		}

		return nullptr;
	}

	Canvas::Canvas()
	: _canvasCam(nullptr)
	{}

	bool Canvas::Init(const glm::vec3& position, const Size& size)
	{
		if (Widget::Init(position, size))
		{
			// Creates camera with size of screen
			const Size& screenSize = CoreManager::GetInstance().GetScreenSize();
			_canvasCam = Camera::CreateOrtho(0.f, (float)screenSize.width, 0.f, (float)screenSize.height, 0.1f, 100.f);
			_canvasCam->SetPosition(glm::vec3(0.f, 0.f, 10.f));
			_canvasCam->SetDrawablesMask(Camera::DEFAULT_CAMERA_UI);
			_canvasCam->SetCameraOrder(5); // Draw after default Cameras, UI on top of everything else

			return true;
		}

		return false;
	}

	void Canvas::OnAttach()
	{
		Entity::OnAttach();

		if (!_scene.expired())
			_scene.lock()->AddCamera(_canvasCam);
	}

	void Canvas::OnDetach()
	{
		Entity::OnDetach();

		if (!_scene.expired())
			_scene.lock()->RemoveCamera(_canvasCam);
	}
}

NS_VG_END
