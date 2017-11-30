#ifndef __VGAUDIOENGINE_H__
#define __VGAUDIOENGINE_H__

#include "VGMacros.h"

#include "VGFMOD.h"

#include <memory>
#include <string>

NS_VG_BEGIN

class DLLAPI AudioEngine
{
public:
	AudioEngine();

	bool Init();

	std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter> CreateSound(const std::string& path, FMOD_MODE modeFlags, FMOD_CREATESOUNDEXINFO* exInfo) const;

	/**
	* Update FMOD::System object every engine tick.
	*/
	void Update();

private:
	std::unique_ptr<FMOD::System, VG_FMOD_Deleter> _fmodSystem;
};

NS_VG_END

#endif // __VGAUDIOENGINE_H__
