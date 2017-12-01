#ifndef __VGAUDIOSOURCE_H__
#define __VGAUDIOSOURCE_H__

#include "VGMacros.h"
#include "base/VGTypes.h"

#include <unordered_map>

namespace FMOD
{
	class ChannelGroup;
}

NS_VG_BEGIN

class AudioSound;

/**
* Little description of how it works FMOD:Channel objects:
* Where the audio is running and produces sound.
* Can be virtualized when requested more channels than the device has, not sound output but still behaviour like a valid one.
* Holds spatial properties.
* Can become invalid if is stolen by the FMOD priority system, be invalid means channel commands no longer affect sound.
*/
class DLLAPI AudioSource
{
public:
	AudioSource();

	/**
	* @return int32 Identifier for handling this sound later. Returns -1 if failed at adding the sound.
	*/
	int32 AddSound(const AudioSound* auSound);

	void PlaySound(const int32 soundId);

private:
	FMOD::ChannelGroup* _fmodChannelGroup;

	int32 _currentId;
	std::unordered_map<int32, const AudioSound*> _sounds;
};

NS_VG_END

#endif // __VGAUDIOSOURCE_H__
