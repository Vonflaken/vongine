#ifndef __VGUIMANAGER_H__
#define __VGUIMANAGER_H__

#include "VGMacros.h"

#include <memory>

NS_VG_BEGIN

namespace ui
{
	struct Message;
	class Canvas;

	class DLLAPI UIManager
	{
	public:
		static UIManager& GetInstance();

		void InjectMessage(const Message& message);

		void ReplaceRootWidget(const std::shared_ptr<Canvas> canvas);
		Canvas* GetRootWidget() { return (_rootWidget.expired()) ? nullptr : _rootWidget.lock().get(); }

	protected:
		UIManager() {}
		virtual ~UIManager() {}

	private:
		std::weak_ptr<Canvas> _rootWidget;
	};
}

NS_VG_END

#endif // __VGUIMANAGER_H__
