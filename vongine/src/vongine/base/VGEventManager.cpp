#include "VGEventManager.h"
#include "base/VGLogger.h"
#include "base/VGInputManager.h"
#include "base/VGCoreManager.h"

NS_VG_BEGIN

EventManager::EventManager()
: _inputMgr(nullptr)
{}

bool EventManager::Init(InputManager* inputMgr)
{
	_inputMgr = inputMgr;

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
		OnMouseMove(ev->motion.x, ev->motion.y, ev->motion.xrel, ev->motion.yrel, (ev->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (ev->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (ev->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		switch (ev->button.button)
		{
		case SDL_BUTTON_LEFT:
		{
			OnLButtonDown(ev->button.x, ev->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT:
		{
			OnRButtonDown(ev->button.x, ev->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE:
		{
			OnMButtonDown(ev->button.x, ev->button.y);
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
			OnLButtonUp(ev->button.x, ev->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT:
		{
			OnRButtonUp(ev->button.x, ev->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE:
		{
			OnMButtonUp(ev->button.x, ev->button.y);
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
	VGLOG_DEBUG("keycode:%d\tmod:%d\tscancode:%d pressed!\n", sym, mod, scancode);

	InputEvent iev;
	iev.device = InputDevice::KEYBOARD;
	iev.type = InputType::DOWN;
	iev.keys[0] = sym;
	iev.keys[1] = mod;

	_inputMgr->OnInputEvent(iev);
}

void EventManager::OnKeyUp(SDL_Keycode sym, uint16 mod, uint16 scancode)
{
	VGLOG_DEBUG("keycode:%d\tmod:%d\tscancode:%d unpressed!\n", sym, mod, scancode);

	InputEvent iev;
	iev.device = InputDevice::KEYBOARD;
	iev.type = InputType::UP;
	iev.keys[0] = sym;
	iev.keys[1] = mod;

	_inputMgr->OnInputEvent(iev);
}

void EventManager::OnMouseMove(int32 mx, int32 my, int32 relx, int32 rely, bool Left, bool Right, bool Middle)
{
	VGLOG_DEBUG("x:%d\ty:%d\n", mx, my);

	onMouseMove(mx, my);
}

void EventManager::OnLButtonDown(int32 mx, int32 my)
{
	VGLOG_DEBUG("Left Click pressed in x:%d\ty:%d\n", mx, my);

	InputEvent iev;
	iev.device = InputDevice::MOUSE;
	iev.type = InputType::DOWN;
	iev.mouseButtons[0] = true;
	iev.mouseButtons[1] = false;

	_inputMgr->OnInputEvent(iev);
}

void EventManager::OnLButtonUp(int32 mx, int32 my)
{
	VGLOG_DEBUG("Left Click unpressed in x:%d\ty:%d\n", mx, my);

	InputEvent iev;
	iev.device = InputDevice::MOUSE;
	iev.type = InputType::UP;
	iev.mouseButtons[0] = true;
	iev.mouseButtons[1] = false;

	_inputMgr->OnInputEvent(iev);
}

void EventManager::OnRButtonDown(int32 mx, int32 my)
{
	VGLOG_DEBUG("Right Click pressed in x:%d\ty:%d\n", mx, my);
}

void EventManager::OnRButtonUp(int32 mx, int32 my)
{
	VGLOG_DEBUG("Right Click unpressed in x:%d\ty:%d\n", mx, my);
}

void EventManager::OnMButtonDown(int32 mx, int32 my)
{
	VGLOG_DEBUG("Middle Click pressed in x:%d\ty:%d\n", mx, my);
}

void EventManager::OnMButtonUp(int32 mx, int32 my)
{
	VGLOG_DEBUG("Middle Click unpressed in x:%d\ty:%d\n", mx, my);
}

void EventManager::OnMouseFocus()
{
	VGLOG_DEBUG("Mouse entered the window!\n");
}

void EventManager::OnMouseBlur()
{
	VGLOG_DEBUG("Mouse leaved the window!\n");
}

void EventManager::OnInputFocus()
{
	VGLOG_DEBUG("Keyboard Focus the window!\n");
}

void EventManager::OnInputBlur()
{
	VGLOG_DEBUG("Keyboar losed focus on the window!\n");
}

void EventManager::OnWindowResized(int32 data1, int32 data2)
{
	VGLOG_DEBUG("Window Resized to: width:%d\theight:%d\n", data1, data2);
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
