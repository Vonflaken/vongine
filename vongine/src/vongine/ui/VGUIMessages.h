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
		MouseButtonUp
	};

	struct DLLAPI Message
	{
		MessageType type;
	};

	struct DLLAPI MessageMouseButtonDown : public Message
	{
		MessageMouseButtonDown() : MessageMouseButtonDown(0, 0, 0) {}
		MessageMouseButtonDown(const uint8 _buttonId, const uint32 _x, const uint32 _y)
		{
			type = MessageType::MouseButtonDown;
			x = _x;
			y = _y;
		}

		uint8 buttonId;
		uint32 x;
		uint32 y;
	};

	struct DLLAPI MessageMouseButtonUp : public Message
	{
		MessageMouseButtonUp() : MessageMouseButtonUp(0, 0, 0) {}
		MessageMouseButtonUp(const uint8 _buttonId, const uint32 _x, const uint32 _y)
		{
			type = MessageType::MouseButtonUp;
			x = _x;
			y = _y;
		}

		uint8 buttonId;
		uint32 x;
		uint32 y;
	};
}

NS_VG_END

#endif // __VGUIMESSAGES_H__
