#ifndef __VGAUDIOSOUND_H__
#define __VGAUDIOSOUND_H__

#include "VGMacros.h"
#include "platform/audio/VGFMOD.h"

#include <memory>
#include <string>

NS_VG_BEGIN

typedef struct {
	FMOD_MODE flags;
	FMOD_CREATESOUNDEXINFO extra;
	bool isStream;
} CreateAuSoundInfo;

/**
* Wrapper for FMOD Sound object.
* FMOD_MODE, more info:
* @url https://www.fmod.com/resources/documentation-api?page=content/generated/FMOD_MODE.html
*/
class DLLAPI AudioSound
{
public:
	AudioSound();

	bool InitWithFilename(const std::string& filename, CreateAuSoundInfo& info = { FMOD_DEFAULT, 0, false });

private:
	std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter> _fmodSound;
};

NS_VG_END

#endif // __VGAUDIOSOUND_H__
