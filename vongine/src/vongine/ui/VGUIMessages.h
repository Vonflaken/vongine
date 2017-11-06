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
		MessageMouseButtonDown() : MessageMouseButtonDown(0, 0.f, 0.f) {}
		MessageMouseButtonDown(const uint8 _buttonId, const float _x, const float _y)
		{
			type = MessageType::MouseButtonDown;
			x = _x;
			y = _y;
		}

		uint8 buttonId;
		float x;
		float y;
	};

	struct DLLAPI MessageMouseButtonUp : public Message
	{
		MessageMouseButtonUp() : MessageMouseButtonUp(0, 0.f, 0.f) {}
		MessageMouseButtonUp(const uint8 _buttonId, const float _x, const float _y)
		{
			type = MessageType::MouseButtonUp;
			x = _x;
			y = _y;
		}

		uint8 buttonId;
		float x;
		float y;
	};
}

NS_VG_END

#endif // __VGUIMESSAGES_H__
