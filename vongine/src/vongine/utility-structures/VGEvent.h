#ifndef __VGEVENT_H__
#define __VGEVENT_H__

#include "VGMacros.h"
#include "utility-structures/VGSignal.h"

NS_VG_BEGIN

/**
* Intended to be a sugar-syntax approach to Signal class, 
* naming is more event like which has more sense in gamedev.
*/

template <typename... Args> 
class DLLAPI Event : protected Signal<Args...>
{
public:
	template <typename T>
	uint32 On(T* instance, void (T::*func)(Args...)) { return ConnectMember(instance, func); }
	
	template <typename T>
	uint32 On(T* instance, void (T::*func)(Args...) const) { return ConnectMember(instance, func); }
	
	uint32 On(const std::function<void(Args...)>& slot) { return Connect(slot); }

	void RemoveCallback(const uint32 id) { Disconnect(id); }
	void RemoveAllCallbacks() { DisconnectAll(); }

	/**
	* Trigger callbacks with functor syntax 'eventInstance(...)'.
	*/
	void operator()(Args... p) { Emit(p...); }
};

NS_VG_END

#endif // __VGEVENT_H__
