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

	void UIManager::ReplaceRootWidget(const std::shared_ptr<Canvas> canvas)
	{
		auto scene = CoreManager::GetInstance().GetActiveScene();
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

NS_VG_END
