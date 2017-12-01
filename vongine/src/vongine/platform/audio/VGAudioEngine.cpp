#include "VGAudioEngine.h"
#include "base/VGTypes.h"
#include "base/VGLogger.h"
#include "resources/VGAudioSound.h"

NS_VG_BEGIN

AudioEngine::AudioEngine()
: _fmodSystem(nullptr, VG_FMOD_Deleter())
{}

bool AudioEngine::Init()
{
	if (!_fmodSystem) // Is not initialized yet?
	{
		FMOD::System* sysPtr = _fmodSystem.get();
		FMOD_RESULT res = FMOD::System_Create(&sysPtr); // Create a FMOD System object
		VG_FMOD_ERRCHECK(res);

		uint32 version;
		res = _fmodSystem->getVersion(&version);
		VG_FMOD_ERRCHECK(res);

		if (version >= FMOD_VERSION)
		{
			void* extraDriverData = 0;
			res = _fmodSystem->init(32, FMOD_INIT_NORMAL, extraDriverData); // Init FMOD System object
			VG_FMOD_ERRCHECK(res);

			return true;
		}
		else
		{
			VGLOG_ERROR("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);

			// Explicit clean resources
			_fmodSystem.reset(nullptr);
		}
	}
	return false;
}

std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter> AudioEngine::CreateSound(const std::string& path, FMOD_MODE modeFlags, FMOD_CREATESOUNDEXINFO* exInfo) const
{
	if (_fmodSystem)
	{
		FMOD::Sound* sound;
		FMOD_RESULT res = _fmodSystem->createSound(path.c_str(), modeFlags, exInfo, &sound); // Create sound
		VG_FMOD_ERRCHECK(res);

		return std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter>(sound, VG_FMOD_Deleter());
	}
	return nullptr;
}

std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter> AudioEngine::CreateStream(const std::string& path, FMOD_MODE modeFlags, FMOD_CREATESOUNDEXINFO* exInfo) const
{
	if (_fmodSystem)
	{
		FMOD::Sound* sound;
		FMOD_RESULT res = _fmodSystem->createStream(path.c_str(), modeFlags, exInfo, &sound); // Create stream
		VG_FMOD_ERRCHECK(res);

		return std::unique_ptr<FMOD::Sound, VG_FMOD_Deleter>(sound, VG_FMOD_Deleter());
	}
	return nullptr;
}

FMOD::ChannelGroup* AudioEngine::CreateChannelGroup() const
{
	if (_fmodSystem)
	{
		FMOD::ChannelGroup* chGroup;
		FMOD_RESULT res = _fmodSystem->createChannelGroup(nullptr, &chGroup);
		VG_FMOD_ERRCHECK(res);
		return chGroup;
	}
	return nullptr;
}

void AudioEngine::Update()
{
	if (_fmodSystem)
	{
		FMOD_RESULT res = _fmodSystem->update();
		VG_FMOD_ERRCHECK(res);
	}
}

void AudioEngine::PlaySound(const AudioSound* auSound, FMOD::ChannelGroup* chGroup)
{
	if (_fmodSystem)
	{
		FMOD_RESULT res = _fmodSystem->playSound(auSound->GetFMODSound(), chGroup, false, nullptr);
		VG_FMOD_ERRCHECK(res);
	}
}

NS_VG_END
