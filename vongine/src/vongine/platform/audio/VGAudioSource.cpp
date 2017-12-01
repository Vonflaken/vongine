#include "VGAudioSource.h"
#include "resources/VGAudioSound.h"
#include "base/VGCoreManager.h"

#include "platform/audio/VGFMOD.h"

NS_VG_BEGIN

AudioSource::AudioSource()
: _currentId(0)
{
	_fmodChannelGroup = CoreManager::GetInstance().AudioEngine()->CreateChannelGroup();
}

int32 AudioSource::AddSound(const AudioSound* auSound)
{
	if (auSound)
	{
		_sounds.insert({ _currentId, auSound });
		return _currentId++;
	}
	return -1;
}

void AudioSource::PlaySound(const int32 soundId)
{
	if (soundId >= 0 && soundId < _currentId) // Is between ids dispatched?
	{
		CoreManager::GetInstance().AudioEngine()->PlaySound(_sounds[soundId], _fmodChannelGroup);
	}
}

NS_VG_END
