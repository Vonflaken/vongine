#ifndef __VGINPUTMANAGER_H__
#define __VGINPUTMANAGER_H__

#include "VGMacros.h"

#include "VGSDL.h"

#include <unordered_map>
#include <functional>

NS_VG_BEGIN

struct DLLAPI InputEvent
{
	enum { Mouse, Keyboard } device;
	enum { Down, Up } type;
	union
	{
		SDL_Scancode key;
		bool mouseButtons[2]; // [0] -> left button. [1] -> right button.
	};
	std::function<void()> callback;

	inline bool operator==(const InputEvent& other) const
	{
		return device == other.device
			&& type == other.type
			&& (device == Mouse && mouseButtons[0] == other.mouseButtons[0] && mouseButtons[1] == other.mouseButtons[1]) 
			|| (device == Keyboard && key == other.key);
	}

	inline bool operator!=(const InputEvent& other) const
	{
		return !(*this == other);
	}
};

class DLLAPI InputManager
{
public:
	void OnInputEvent(const InputEvent& ev);

	void AddAction(const std::string& name, const InputEvent& ev);

	/**
	* Check whereas or no an action was performed in current frame.
	* @param name Name of the action.
	*/
	bool TestAction(const std::string& name) const;

	/**
	* Remove all input events stored in current frame
	*/
	void ReleaseFrameEvents();

private:
	std::unordered_map<const std::string, InputEvent> _userActions;

	std::vector<InputEvent> _frameEvents; // Store input events performed during the current frame
};

NS_VG_END

#endif // __VGINPUTMANAGER_H__
