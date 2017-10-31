#ifndef __VGEVENTMANAGER_H__
#define __VGEVENTMANAGER_H__

#include "VGMacros.h"
#include "base/VGTypes.h"
#include "utility-structures/VGEvent.h"

#include "VGSDL.h"

NS_VG_BEGIN

class InputManager;

class DLLAPI EventManager
{
public:
	EventManager();

	/**
	* Set InputManager that the engine gonna use at the moment, should be invalidated and therefore the reference updated if ever change the active InputMgr.
	*/
	bool Init(InputManager* inputMgr);

	void ProcessEvents();

private:
	/**
	* Handle SDL Event.
	*/
	void OnEvent(SDL_Event* ev);

	/************************************************************ Internal handling of system events */
	void OnExitApp();

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


	/************************************************************ Custom engine events */
	/**
	* Call to every Entity::UpdateLogic() function that user enabled previously.
	*/
	void OnUpdateLogic(const float deltaTime);

public:
	/********************************************************* System events which user can hook */
	Event<> onExitApp;
	Event<int32, int32> onMouseMove;


	/********************************************************* Custom events which user can hook */
	Event<float> onUpdateLogic;

private:
	InputManager* _inputMgr;
};

NS_VG_END

#endif // __VGEVENTMANAGER_H__
