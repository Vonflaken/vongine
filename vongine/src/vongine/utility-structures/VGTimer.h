#ifndef __VGTIMER_H__
#define __VGTIMER_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include "VGSDL.h"

NS_VG_BEGIN

/**
* Simple Timer helper class for tracking how is going a countdown.
* All time values are measured in miliseconds.
*/
class DLLAPI Timer
{
public:
	/**
	* @param duration In miliseconds.
	*/
	Timer()
	: _duration(0)
	, _startTime(0)
	{}

	void Start(const uint32 duration) 
	{ 
		_duration = duration;
		_startTime = SDL_GetTicks(); 
	}
	bool IsComplete() const { return SDL_GetTicks() >= (_startTime + _duration); }

private:
	uint32 _startTime;
	uint32 _duration;
};

NS_VG_END

#endif // __VGTIMER_H__
