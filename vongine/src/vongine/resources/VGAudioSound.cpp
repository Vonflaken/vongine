#include "VGAudioSound.h"
#include "platform/VGFile.h"
#include "base/VGCoreManager.h"

NS_VG_BEGIN

std::shared_ptr<AudioSound> AudioSound::CreateSound(const std::string& filename, const FMOD_MODE modeFlags)
{
	auto sound = std::make_shared<AudioSound>();
	if (sound->InitWithFilename(filename, modeFlags))
	{
		return sound;
	}
	return nullptr;
}

std::shared_ptr<AudioSound> AudioSound::CreateStream(const std::string& filename, const FMOD_MODE modeFlags)
{
	auto sound = std::make_shared<AudioSound>();
	if (sound->InitWithFilename(filename, modeFlags, true))
	{
		return sound;
	}
	return nullptr;
}

AudioSound::AudioSound()
: _fmodSound(nullptr, VG_FMOD_Deleter())
{}

bool AudioSound::InitWithFilename(const std::string& filename, const FMOD_MODE modeFlags, const bool isStream)
{
	if (!filename.empty())
	{
		// Get full path to sound file
		std::string fullPathToSound = File::GetFullPathOfResource(filename);

		if (isStream)
		{
			// Create stream
		}
		else
		{
			// Create sound
			_fmodSound = CoreManager::GetInstance().AudioEngine()->CreateSound(fullPathToSound, modeFlags, 0);
		}
	}
	return false;
}

NS_VG_END
