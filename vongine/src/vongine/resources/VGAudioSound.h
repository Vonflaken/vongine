#ifndef __VGAUDIOSOUND_H__
#define __VGAUDIOSOUND_H__

#include "VGMacros.h"
#include "platform/audio/VGFMOD.h"

#include <memory>
#include <string>

NS_VG_BEGIN

struct CreateAuSoundInfo 
{
	CreateAuSoundInfo()
	: flags(FMOD_DEFAULT)
	, extra({ 0 })
	, isStream(false)
	{}

	FMOD_MODE flags;
	FMOD_CREATESOUNDEXINFO extra;
	bool isStream;
};

/**
* Wrapper for FMOD Sound object.
* FMOD_MODE, more info:
* @url https://www.fmod.com/resources/documentation-api?page=content/generated/FMOD_MODE.html
*/
class DLLAPI AudioSound
{
public:
	AudioSound();

	bool InitWithFilename(const std::string& filename, CreateAuSoundInfo& info);

private:
	std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter> _fmodSound;
};

NS_VG_END

#endif // __VGAUDIOSOUND_H__
