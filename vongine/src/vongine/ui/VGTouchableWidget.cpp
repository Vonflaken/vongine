#include "VGTouchableWidget.h"
#include "ui/VGUIMessages.h"

NS_VG_BEGIN

namespace ui
{
	TouchableWidget::TouchableWidget()
	: _pressed(false)
	{}

	void TouchableWidget::HandleMessage(const Message& message)
	{
		switch (message.type)
		{
		case MessageType::MouseButtonDown:
		{
			_pressed = true;
			onPressed(this);
			break;
		}
		case MessageType::MouseButtonUp:
		{ // User clicked
			if (_pressed)
			{
				onClick(this);
				_pressed = false;
			}
			break;
		}
		case MessageType::PointerHoverOut:
		{
			// Restore state, pointer is now out of bounds of this Widget
			_pressed = false;
			break;
		}
		}
	}
}

NS_VG_END
