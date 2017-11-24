#ifndef __VGUIMESSAGES_H__
#define __VGUIMESSAGES_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

namespace ui
{
	enum class MessageType
	{
		MouseButtonDown, 
		MouseButtonUp, 
		PointerMove, 
		PointerHoverIn, 
		PointerHoverOut
	};

	struct DLLAPI Message
	{
		MessageType type;
	};

	struct DLLAPI MessageMouseButtonDown : public Message
	{
		MessageMouseButtonDown() : MessageMouseButtonDown(0, 0, 0) {}
		MessageMouseButtonDown(const uint8 buttonId_, const uint32 x_, const uint32 y_)
		{
			type = MessageType::MouseButtonDown;
			buttonId = buttonId_;
			x = x_;
			y = y_;
		}

		uint8 buttonId;
		uint32 x;
		uint32 y;
	};

	struct DLLAPI MessageMouseButtonUp : public Message
	{
		MessageMouseButtonUp() : MessageMouseButtonUp(0, 0, 0) {}
		MessageMouseButtonUp(const uint8 buttonId_, const uint32 x_, const uint32 y_)
		{
			type = MessageType::MouseButtonUp;
			buttonId = buttonId_;
			x = x_;
			y = y_;
		}

		uint8 buttonId;
		uint32 x;
		uint32 y;
	};

	struct DLLAPI MessagePointerMove : public Message
	{
		MessagePointerMove() : MessagePointerMove(0, 0) {}
		MessagePointerMove(const uint32 x_, const uint32 y_)
		{
			type = MessageType::PointerMove;
			x = x_;
			y = y_;
		}

		uint32 x;
		uint32 y;
	};

	struct DLLAPI MessagePointerHoverIn : public Message
	{
		MessagePointerHoverIn()
		{
			type = MessageType::PointerHoverIn;
		}
	};

	struct DLLAPI MessagePointerHoverOut : public Message
	{
		MessagePointerHoverOut()
		{
			type = MessageType::PointerHoverOut;
		}
	};
}

NS_VG_END

#endif // __VGUIMESSAGES_H__
