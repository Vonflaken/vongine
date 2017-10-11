#include "VGInputManager.h"

NS_VG_BEGIN

void InputManager::OnInputEvent(const InputEvent& ev)
{
	_frameEvents.push_back(ev);
}

void InputManager::AddAction(const std::string& name, const InputEvent& ev)
{
	_userActions[name] = ev;
}

bool InputManager::TestAction(const std::string& name) const
{
	InputEvent actionEvent = _userActions.at(name);
	for (uint32 i = 0; i < _frameEvents.size(); i++)
	{
		if (_frameEvents[i] == actionEvent)
			return true;
	}
}

void InputManager::ReleaseFrameEvents()
{
	_frameEvents.clear();
}

NS_VG_END
