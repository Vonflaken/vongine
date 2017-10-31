#include "VGInputManager.h"
#include "base/VGCoreManager.h"

NS_VG_BEGIN

InputManager::InputManager()
: _mousePosX(0)
, _mousePosY(0)
{}

bool InputManager::Init()
{
	CoreManager::GetInstance().EventMgr()->onMouseMove.On(VG_CALLBACK(OnMouseMove, this));

	return true;
}

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

void InputManager::GetMousePos(int32* const mousex, int32* const mousey) const
{
	*mousex = _mousePosX;
	*mousey = _mousePosY;
}

void InputManager::ClearFrameEvents()
{
	_frameEvents.clear();
}

void InputManager::OnMouseMove(const int32 mousex, const int32 mousey)
{
	_mousePosX = mousex;
	_mousePosY = mousey;
}

NS_VG_END
