#ifndef __VGAUDIOSOUND_H__
#define __VGAUDIOSOUND_H__

#include "VGMacros.h"
#include "platform/audio/VGFMOD.h"

#include <memory>
#include <string>

NS_VG_BEGIN

/**
* Wrapper for FMOD Sound object.
* FMOD_MODE, more info:
* @url https://www.fmod.com/resources/documentation-api?page=content/generated/FMOD_MODE.html
*/
class DLLAPI AudioSound
{
public:
	/**
	* @param modeFlags 
	*/
	static std::shared_ptr<AudioSound> CreateSound(const std::string& filename, const FMOD_MODE modeFlags = FMOD_DEFAULT);
	static std::shared_ptr<AudioSound> CreateStream(const std::string& filename, const FMOD_MODE modeFlags = FMOD_DEFAULT);

	AudioSound();

	bool InitWithFilename(const std::string& filename, const FMOD_MODE modeFlags, const bool isStream = false);

private:
	std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter> _fmodSound;
};

NS_VG_END

#endif // __VGAUDIOSOUND_H__
