#include "VGEventManager.h"
#include "base/VGLogger.h"
#include "base/VGInputManager.h"
#include "base/VGCoreManager.h"
#include "ui/VGUIManager.h"
#include "ui/VGUIMessages.h"

NS_VG_BEGIN

EventManager::EventManager()
: _inputMgr(nullptr)
, _coreMgr(nullptr)
{}

bool EventManager::Init(InputManager* inputMgr)
{
	_inputMgr = inputMgr;
	_coreMgr = &CoreManager::GetInstance();

	return true;
}

void EventManager::ProcessEvents()
{
	// Poll system events, mainly from input devices.
	// Some custom user defined events as well if uses SDL event system.
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		OnEvent(&e);
	}

	// Update logic in all entities
	OnUpdateLogic(CoreManager::GetInstance().GetDeltaTime());

	// Clear input events that popped in current frame.
	// It's suppose that input events are tested by user in Update Logic of Entities,
	// so after that we can flush them.
	// Also Input Mgr should saves the state of input devices so they would be available for polling further in frame.
	_inputMgr->ClearFrameEvents();
}

void EventManager::OnEvent(SDL_Event* ev)
{
	uint32 screenHeight = _coreMgr->GetScreenSize().height;

	switch (ev->type)
	{
	case SDL_WINDOWEVENT:
	{
		switch (ev->window.event)
		{
		case SDL_WINDOWEVENT_ENTER:
		{
			OnMouseFocus();
			break;
		}
		case SDL_WINDOWEVENT_LEAVE:
		{
			OnMouseBlur();
			break;
		}
		case SDL_WINDOWEVENT_FOCUS_GAINED:
		{
			OnInputFocus();
			break;
		}
		case SDL_WINDOWEVENT_FOCUS_LOST:
		{
			OnInputBlur();
			break;
		}
		case SDL_WINDOWEVENT_SHOWN:
		{
			break;
		}
		case SDL_WINDOWEVENT_HIDDEN:
		{
			break;
		}
		case SDL_WINDOWEVENT_EXPOSED:
		{
			break;
		}
		case SDL_WINDOWEVENT_MOVED:
		{
			break;
		}
		case SDL_WINDOWEVENT_RESIZED:
		{
			OnWindowResized(ev->window.data1, ev->window.data2);
			break;
		}
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			break;
		}
		case SDL_WINDOWEVENT_MINIMIZED:
		{
			break;
		}
		case SDL_WINDOWEVENT_MAXIMIZED:
		{
			break;
		}
		case SDL_WINDOWEVENT_RESTORED:
		{
			break;
		}
		case SDL_WINDOWEVENT_CLOSE:
		{
			break;
		}
		}
		break;
	} // End Window Events
	case SDL_QUIT:
	{
		OnExitApp();
		break;
	}
	case SDL_KEYDOWN:
	{
		OnKeyDown(ev->key.keysym.sym, ev->key.keysym.mod, ev->key.keysym.scancode);
		break;
	}
	case SDL_KEYUP:
	{
		OnKeyUp(ev->key.keysym.sym, ev->key.keysym.mod, ev->key.keysym.scancode);
		break;
	}
	case SDL_MOUSEMOTION:
	{
		// Flip y-axis to match positive-up
		OnMouseMove(ev->motion.x, screenHeight - ev->motion.y, ev->motion.xrel, -(ev->motion.yrel), (ev->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (ev->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (ev->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		switch (ev->button.button)
		{
		case SDL_BUTTON_LEFT:
		{
			// Flip y-axis to match positive-up
			OnLButtonDown(ev->button.x, screenHeight - ev->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT:
		{
			// Flip y-axis to match positive-up
			OnRButtonDown(ev->button.x, screenHeight - ev->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE:
		{
			// Flip y-axis to match positive-up
			OnMButtonDown(ev->button.x, screenHeight - ev->button.y);
			break;
		}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		switch (ev->button.button)
		{
		case SDL_BUTTON_LEFT:
		{
			// Flip y-axis to match positive-up
			OnLButtonUp(ev->button.x, screenHeight - ev->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT:
		{
			// Flip y-axis to match positive-up
			OnRButtonUp(ev->button.x, screenHeight - ev->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE:
		{
			// Flip y-axis to match positive-up
			OnMButtonUp(ev->button.x, screenHeight - ev->button.y);
			break;
		}
		}
		break;
	}

	case SDL_JOYAXISMOTION:
	{
		OnJoyAxis(ev->jaxis.which, ev->jaxis.axis, ev->jaxis.value);
		break;
	}
	case SDL_JOYBALLMOTION:
	{
		OnJoyBall(ev->jball.which, ev->jball.ball, ev->jball.xrel, ev->jball.yrel);
		break;
	}
	case SDL_JOYHATMOTION:
	{
		OnJoyHat(ev->jhat.which, ev->jhat.hat, ev->jhat.value);
		break;
	}
	case SDL_JOYBUTTONDOWN:
	{
		OnJoyButtonDown(ev->jbutton.which, ev->jbutton.button);
		break;
	}
	case SDL_JOYBUTTONUP:
	{
		OnJoyButtonUp(ev->jbutton.which, ev->jbutton.button);
		break;
	}
	default:
	{
		OnUser(ev->user.type, ev->user.code, ev->user.data1, ev->user.data2);
		break;
	}
	}
}

/************************************************************ Internal handling of system events */

void EventManager::OnExitApp() 
{
	onExitApp();
}

void EventManager::OnKeyDown(SDL_Keycode sym, uint16 mod, uint16 scancode)
{
	//VGLOG_DEBUG("keycode:%d\tmod:%d\tscancode:%d pressed!", sym, mod, scancode);

	// Pass event to Input Manager
	InputEvent iev;
	iev.device = InputDevice::KEYBOARD;
	iev.type = InputType::DOWN;
	iev.keys[0] = sym;
	iev.keys[1] = mod;

	_inputMgr->OnInputEvent(iev);
}

void EventManager::OnKeyUp(SDL_Keycode sym, uint16 mod, uint16 scancode)
{
	//VGLOG_DEBUG("keycode:%d\tmod:%d\tscancode:%d unpressed!", sym, mod, scancode);

	// Pass event to Input Manager
	InputEvent iev;
	iev.device = InputDevice::KEYBOARD;
	iev.type = InputType::UP;
	iev.keys[0] = sym;
	iev.keys[1] = mod;

	_inputMgr->OnInputEvent(iev);
}

void EventManager::OnMouseMove(int32 mx, int32 my, int32 relx, int32 rely, bool Left, bool Right, bool Middle)
{
	//VGLOG_DEBUG("x:%d\ty:%d\trelx:%d\trely:%d", mx, my, relx, rely);

	onMouseMove(mx, my);

	// Pass event to UI system
	ui::MessagePointerMove uiMsg(mx, my);
	ui::UIManager::GetInstance().InjectMessage(uiMsg);
}

void EventManager::OnLButtonDown(int32 mx, int32 my)
{
	//VGLOG_DEBUG("Left Click pressed in x:%d\ty:%d", mx, my);

	// Pass event to Input Manager
	InputEvent iev;
	iev.device = InputDevice::MOUSE;
	iev.type = InputType::DOWN;
	iev.mouseButtonId = 0;

	_inputMgr->OnInputEvent(iev);

	// Pass event to UI system
	ui::MessageMouseButtonDown uiMsg(0, mx, my);
	ui::UIManager::GetInstance().InjectMessage(uiMsg);
}

void EventManager::OnLButtonUp(int32 mx, int32 my)
{
	//VGLOG_DEBUG("Left Click unpressed in x:%d\ty:%d", mx, my);

	// Pass event to Input Manager
	InputEvent iev;
	iev.device = InputDevice::MOUSE;
	iev.type = InputType::UP;
	iev.mouseButtonId = 0;

	_inputMgr->OnInputEvent(iev);

	// Pass event to UI system
	ui::MessageMouseButtonUp uiMsg(0, mx, my);
	ui::UIManager::GetInstance().InjectMessage(uiMsg);
}

void EventManager::OnRButtonDown(int32 mx, int32 my)
{
	//VGLOG_DEBUG("Right Click pressed in x:%d\ty:%d", mx, my);
}

void EventManager::OnRButtonUp(int32 mx, int32 my)
{
	//VGLOG_DEBUG("Right Click unpressed in x:%d\ty:%d", mx, my);
}

void EventManager::OnMButtonDown(int32 mx, int32 my)
{
	//VGLOG_DEBUG("Middle Click pressed in x:%d\ty:%d", mx, my);
}

void EventManager::OnMButtonUp(int32 mx, int32 my)
{
	//VGLOG_DEBUG("Middle Click unpressed in x:%d\ty:%d", mx, my);
}

void EventManager::OnMouseFocus()
{
	//VGLOG_DEBUG("Mouse entered the window!");
}

void EventManager::OnMouseBlur()
{
	//VGLOG_DEBUG("Mouse leaved the window!");
}

void EventManager::OnInputFocus()
{
	//VGLOG_DEBUG("Keyboard Focus the window!");
}

void EventManager::OnInputBlur()
{
	//VGLOG_DEBUG("Keyboar losed focus on the window!");
}

void EventManager::OnWindowResized(int32 data1, int32 data2)
{
	//VGLOG_DEBUG("Window Resized to: width:%d\theight:%d", data1, data2);
}

void EventManager::OnJoyAxis(uint8 which, uint8 axis, int16 value) {}

void EventManager::OnJoyBall(uint8 which, uint8 ball, int16 xrel, int16 yrel) {}

void EventManager::OnJoyHat(uint8 which, uint8 hat, uint8 button) {}

void EventManager::OnJoyButtonDown(uint8 which, uint8 button) {}

void EventManager::OnJoyButtonUp(uint8 which, uint8 button) {}

void EventManager::OnUser(uint8 type, int32 code, void* data1, void* data2) {}


/************************************************************ Custom engine events */
void EventManager::OnUpdateLogic(const float deltaTime)
{
	onUpdateLogic(deltaTime);
}

NS_VG_END
