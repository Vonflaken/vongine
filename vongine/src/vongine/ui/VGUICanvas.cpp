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
		if (canvas->Init(size))
		{
			return canvas;
		}

		return nullptr;
	}

	Canvas::Canvas()
	: _canvasCam(nullptr)
	{}

	bool Canvas::Init(const Size& size)
	{
		Widget::Init(size);

		// Creates camera with size of screen
		const Size& screenSize = CoreManager::GetInstance().GetScreenSize();
		_canvasCam = Camera::CreateOrtho(0, screenSize.width, 0, screenSize.height, 0.1f, 100.f);
	}

	void Canvas::OnAttach()
	{
		Entity::OnAttach();

		CoreManager::GetInstance().GetActiveScene()->AddCamera(_canvasCam);
	}

	void Canvas::OnDetach()
	{
		Entity::OnDetach();

		CoreManager::GetInstance().GetActiveScene()->RemoveCamera(_canvasCam);
	}
}

NS_VG_END
