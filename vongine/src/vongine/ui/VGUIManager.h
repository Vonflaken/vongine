#ifndef __VGUIMANAGER_H__
#define __VGUIMANAGER_H__

#include "VGMacros.h"

#include <memory>

NS_VG_BEGIN

class Scene;

namespace ui
{
	struct Message;
	class Canvas;

	class DLLAPI UIManager
	{
	public:
		static UIManager& GetInstance();

		void InjectMessage(const Message& message);

		/**
		* Drop current root widget and put new one instead. 
		* @param inScene Scene where root widget belongs. Uses current active scene if null provided.
		*/
		void ReplaceRootWidget(const std::shared_ptr<Canvas> canvas, Scene * const inScene = nullptr);
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
