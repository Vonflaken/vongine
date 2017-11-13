#include "VGUIManager.h"
#include "ui/VGUICanvas.h"
#include "ui/VGUIMessages.h"
#include "base/VGCoreManager.h"
#include "base/VGScene.h"

NS_VG_BEGIN

namespace ui
{
	UIManager& UIManager::GetInstance()
	{
		static UIManager* instance = new UIManager();
		return *instance;
	}

	void UIManager::InjectMessage(const Message& message)
	{
		if (!_rootWidget.expired()) 
			_rootWidget.lock()->InjectMessage(message);
	}

	void UIManager::ReplaceRootWidget(const std::shared_ptr<Canvas> canvas, Scene * const inScene)
	{
		auto scene = inScene;
		if (!scene) // Take current active scene if null provided
		{
			scene = CoreManager::GetInstance().GetActiveScene();
		}

		if (scene) // Ensure a valid ptr
		{
			if (!_rootWidget.expired())
			{
				// Remove old Canvas from scene
				scene->DetachChildRecursive(_rootWidget.lock());
			}

			// Add new Canvas to scene
			scene->AddChild(canvas);
			// Set new Canvas as root Widget
			_rootWidget = canvas;
		}
	}
}

NS_VG_END
