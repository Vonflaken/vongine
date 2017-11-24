#ifndef __VGTOUCHABLEWIDGET_H__
#define __VGTOUCHABLEWIDGET_H__

#include "VGMacros.h"
#include "ui/VGWidget.h"
#include "utility-structures/VGEvent.h"

NS_VG_BEGIN

namespace ui
{
	/**
	* onClick event in Widget is triggered if presses and releases without loosing the focus on the TouchableWidget between operations.
	* If presses and pointer looses the focus on the Widget the event is invalidated.
	*/
	class DLLAPI TouchableWidget : public Widget
	{
	public:
		TouchableWidget();

		void HandleMessage(const Message& message) override;

	public:
		Event<Widget*> onPressed;
		Event<Widget*> onClick;

	protected:
		bool _pressed;
	};
}

NS_VG_END

#endif // __VGTOUCHABLEWIDGET_H__
