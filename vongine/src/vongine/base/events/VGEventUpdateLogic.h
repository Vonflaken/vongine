#ifndef __VGEVENTUPDATELOGIC_H__
#define __VGEVENTUPDATELOGIC_H__

#include "utility-structures/VGSignal.h"
#include "base/VGEntity.h"

NS_VG_BEGIN

class DLLAPI EventUpdateLogic : protected Signal<float>
{
public:
	uint32 On(Entity* target) 
	{
		return Connect([=](float deltaTime) {
			if (target->IsActive())
				target->UpdateLogic(deltaTime);
		});
	}

	void RemoveCallback(const uint32 id) { Disconnect(id); }
	void RemoveAllCallbacks() { DisconnectAll(); }

	/**
	* Trigger callbacks with functor syntax 'eventInstance(...)'.
	*/
	void operator()(float deltaTime) { Emit(deltaTime); }
};

NS_VG_END

#endif // __VGEVENTUPDATELOGIC_H__
