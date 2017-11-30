#include "VGAudioSound.h"
#include "platform/VGFile.h"
#include "base/VGCoreManager.h"

NS_VG_BEGIN

AudioSound::AudioSound()
: _fmodSound(nullptr, VG_FMOD_Deleter())
{}

bool AudioSound::InitWithFilename(const std::string& filename, CreateAuSoundInfo& info)
{
	if (!filename.empty())
	{
		// Get full path to sound file
		std::string fullPathToSound = File::GetFullPathOfResource(filename);

		if (info.isStream)
		{
			// Create stream
			_fmodSound = CoreManager::GetInstance().AudioEngine()->CreateStream(fullPathToSound, info.flags, &info.extra);
		}
		else
		{
			// Create sound
			_fmodSound = CoreManager::GetInstance().AudioEngine()->CreateSound(fullPathToSound, info.flags, &info.extra);
		}
	}
	return false;
}

NS_VG_END
