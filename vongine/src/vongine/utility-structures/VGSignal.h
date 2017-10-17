#ifndef __VGSIGNAL_H__
#define __VGSIGNAL_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include <functional>
#include <map>

NS_VG_BEGIN

template <typename... Args>
class DLLAPI Signal
{
public:
	Signal() : _currentId(0) {}
	virtual ~Signal() {}

	/**
	* Connects a member function to this Signal.
	*/
	template <typename T>
	uint32 ConnectMember(T* instance, void (T::*func)(Args...))
	{
		return Connect([=](Args... args) {
			(instance->*func)(args...);
		});
	}

	/**
	* Connects a const member function to this Signal.
	*/
	template <typename T>
	uint32 ConnectMember(T* instance, void (T::*func)(Args...) const)
	{
		return Connect([=](Args... args) {
			(instance->*func)(args...);
		});
	}

	/**
	* Connects a std::function to the signal.
	* @return uint32 Can be used to disconnect the function again.
	*/
	uint32 Connect(const std::function<void(Args...)>& slot)
	{
		_slots.insert(std::make_pair(++_currentId, slot));
		return _currentId;
	}

	/**
	* Disconnects a previously connected function.
	*/
	void Disconnect(const uint32 id)
	{
		_slots.erase(id);
	}

	/**
	* Disconnects all previously connected functions.
	*/
	void DisconnectAll()
	{
		_slots.clear();
	}

	/**
	* Calls all connected functions.
	*/
	void Emit(Args... p)
	{
		for (auto it : _slots)
		{
			it.second(p...);
		}
	}

private:
	std::map<uint32, std::function<void(Args...)>> _slots;
	uint32 _currentId;
};

NS_VG_END

#endif // __VGSIGNAL_H__
