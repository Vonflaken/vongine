#ifndef __VGAUDIOENGINE_H__
#define __VGAUDIOENGINE_H__

#include "VGMacros.h"

#include "VGFMOD.h"

#include <memory>
#include <string>

NS_VG_BEGIN

class AudioSound;

class DLLAPI AudioEngine
{
public:
	AudioEngine();

	bool Init();

	std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter> CreateSound(const std::string& path, FMOD_MODE modeFlags, FMOD_CREATESOUNDEXINFO* exInfo) const;
	std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter> CreateStream(const std::string& path, FMOD_MODE modeFlags, FMOD_CREATESOUNDEXINFO* exInfo) const;

	FMOD::ChannelGroup* CreateChannelGroup() const;

	/**
	* Update FMOD::System object every engine tick.
	*/
	void Update();

	/**
	* @param chGroup FMOD::ChannelGroup parent of channel assigned for running this sound. Optional. Nullptr will set master FMOD::ChannelGroup.
	*/
	void PlaySound(const AudioSound* auSound, FMOD::ChannelGroup* chGroup = nullptr);

private:
	std::unique_ptr<FMOD::System, VG_FMOD_Deleter> _fmodSystem;
};

NS_VG_END

#endif // __VGAUDIOENGINE_H__
