#ifndef __VGEVENTMANAGER_H__
#define __VGEVENTMANAGER_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include "VGSDL.h"

NS_VG_BEGIN

class DLLAPI EventManager
{
public:
	void ProcessEvents();

	void OnEvent(SDL_Event* ev);

	void OnExit();

	void OnKeyDown(SDL_Keycode sym, uint16 mod, uint16 scancode);

	void OnKeyUp(SDL_Keycode sym, uint16 mod, uint16 scancode);

	void OnMouseMove(int32 mx, int32 my, int32 relx, int32 rely, bool left, bool right, bool middle);

	void OnLButtonDown(int32 mx, int32 my);

	void OnLButtonUp(int32 mx, int32 my);

	void OnRButtonDown(int32 mx, int32 my);

	void OnRButtonUp(int32 mx, int32 my);

	void OnMButtonDown(int32 mx, int32 my);

	void OnMButtonUp(int32 mx, int32 my);

	void OnMouseFocus();

	void OnMouseBlur();

	void OnInputFocus();

	void OnInputBlur();

	void OnWindowResized(int32 data1, int32 data2);

	void OnJoyAxis(uint8 which, uint8 axis, int16 value);

	void OnJoyBall(uint8 which, uint8 ball, int16 xrel, int16 yrel);

	void OnJoyHat(uint8 which, uint8 hat, uint8 button);

	void OnJoyButtonDown(uint8 which, uint8 button);

	void OnJoyButtonUp(uint8 which, uint8 button);

	void OnUser(uint8 type, int32 code, void* data1, void* data2);
};

NS_VG_END

#endif // __VGEVENTMANAGER_H__
