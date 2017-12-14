#ifndef __VGINPUTMANAGER_H__
#define __VGINPUTMANAGER_H__

#include "VGMacros.h"

#include "VGSDL.h"

#include <unordered_map>
#include <functional>

NS_VG_BEGIN

enum class InputDevice
{
	MOUSE, 
	KEYBOARD
};

enum class InputType
{
	DOWN, 
	UP
};

typedef uint32 VG_Keystate;
enum
{
	VGKS_UNPRESSED = 0,
	VGKS_PRESSED
};

struct DLLAPI InputEvent
{
	InputDevice device;
	InputType type;
	union
	{
		/**
		* Keyboard keys.
		* [0] -> SDL_Keycode.
		* [1] -> OR'd combination of the modifier keys (Ctr, Alt...). Bitwise AND op against mod keys constant (KMOD_*) to reveal what are pushed.
		*/
		int32 keys[2];
		/**
		* Mouse button.
		* 0 -> left button.
		* 1 -> right button.
		* 2 -> mid button.
		*/
		uint8 mouseButtonId;
	};

	/**
	* Modifier keys are not tested here, still included in the event.
	*/
	inline bool operator==(const InputEvent& other) const
	{
		return device == other.device
			&& type == other.type
			&& (device == InputDevice::MOUSE && mouseButtonId == other.mouseButtonId) 
			|| (device == InputDevice::KEYBOARD && keys[0] == other.keys[0]);
	}

	inline bool operator!=(const InputEvent& other) const
	{
		return !(*this == other);
	}
};

class DLLAPI InputManager
{
public:
	InputManager();

	bool Init();

	void OnInputEvent(const InputEvent& ev);
	
	void AddAction(const std::string& name, const InputEvent& ev);

	/**
	* Check whereas or no an action was performed in current frame.
	* @param name Name of the action.
	*/
	bool TestAction(const std::string& name) const;

	void GetMousePos(int32* const mousex, int32* const mousey) const;

	/**
	* Test if certain keyboard key is pressed.
	*/
	bool IsKeyPressed(const SDL_Keycode keycode) { return _keysState[keycode] == VGKS_PRESSED; }
	/**
	* Test if certain button of the mouse is pressed.
	* @param buttonId Values are: '0' for left button, '1' for middle button and '2' for right button.
	*/
	bool IsMouseButtonPressed(const uint32 buttonId);

	/**
	* Remove all input events stored in current frame
	*/
	void ClearFrameEvents();

private:
	void OnMouseMove(const int32 mousex, const int32 mousey);

private:
	std::unordered_map<std::string, InputEvent> _userActions;

	std::vector<InputEvent> _frameEvents; // Store input events performed during the current frame

	int32 _mousePosX, _mousePosY;
	/**
	* Keys: It uses SDL_Keycode values.
	* Values: It uses custom VG_Keystate, defined above this class declaration.
	*/
	std::unordered_map<int32, uint32> _keysState;
};

NS_VG_END

#endif // __VGINPUTMANAGER_H__
